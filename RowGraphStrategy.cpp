//
// Created by pentester on 7/18/25.
//


#include "RowGraphStrategy.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <thread>

#include "iPlayer.h"

std::vector<std::pair<int, int> > RowGraphStrategy::graph::compress(const std::vector<int> &node_info) noexcept {
	std::vector<std::pair<int, int> > node_info_compressed;

	for (int i = 0; i < node_info.size(); i++) {
		if (!node_info_compressed.size() || node_info_compressed.back().first != node_info[i]) {
			node_info_compressed.emplace_back(node_info[i], 0);
		}
		node_info_compressed.back().second++;
	}
	return node_info_compressed;
}

void RowGraphStrategy::graph::brute_nodes(int n, int k, std::vector<std::vector<std::pair<int, int> > > &result,
                                          int lst) noexcept {
	static std::vector<int> current_groups;

	if (k == 0) {
		result.push_back(compress(current_groups));

		return;
	}

	for (int i = lst; i <= n; i++) {
		current_groups.push_back(i);
		brute_nodes(n - i, k - 1, result, i);
		current_groups.pop_back();
	}
}

void RowGraphStrategy::graph::prepare_nodes() noexcept {
	nodes[std::vector<std::pair<int, int> >(0)] = std::make_shared<Node>(std::vector<std::pair<int, int> >(0));
	// root node

	for (int i = 1; i <= n_; i++) {
		std::vector<std::vector<std::pair<int, int> > > result;
		brute_nodes(n_ - i + 1, i, result);

		for (const auto &pairs: result) {
			nodes[pairs] = std::make_shared<Node>(pairs);
		}
	}
}

void RowGraphStrategy::graph::build_graph() noexcept {
	using vector_nodes = std::vector<std::pair<std::vector<std::pair<int, int> >, std::shared_ptr<Node> > >;

	vector_nodes node_list(nodes.begin(), nodes.end());

	auto worker = [a_ = this->a_, b_ = this->b_, n_ = this->n_, &nodes = this->nodes](
		size_t start, size_t end, const vector_nodes &local_nodes) {
		for (size_t idx = start; idx < end; idx++) {
			const auto &[node_info_compressed, node] = local_nodes[idx];
			auto [sum, cnt] = std::accumulate(node_info_compressed.begin(), node_info_compressed.end(),
			                                  std::make_pair(0, 0),
			                                  [](std::pair<int, int> ac, std::pair<int, int> cur) {
				                                  return std::make_pair(ac.first + cur.first * cur.second,
				                                                        ac.second + cur.second);
			                                  });

			for (int k = a_; k <= b_; k++) {
				if (sum + k + cnt - 1 <= n_) {
					for (int j = 0; j < node_info_compressed.size(); j++) {
						auto cur = node_info_compressed;

						if (!(--cur[j].second)) {
							cur.erase(cur.begin() + j);
						}

						auto new_len = node_info_compressed[j].first + k;
						bool merged = false;
						for (auto &pr: cur) {
							if (pr.first == new_len) {
								pr.second++;
								merged = true;
								break;
							}
						}

						if (!merged) {
							auto it = std::upper_bound(
								cur.begin(), cur.end(), new_len,
								[](int v, const std::pair<int, int> &pr) {
									return v < pr.first;
								}
							);
							cur.insert(it, {new_len, 1});
						}

						auto it_node = nodes.find(cur);
						auto prev = it_node->second;
						node->next_nodes.insert(prev);
						prev->is_terminate = false;
					}
				}

				if (sum + k + cnt <= n_) {
					auto next = node_info_compressed;

					bool merged = false;
					for (auto &pr: next) {
						if (pr.first == k) {
							pr.second++;
							merged = true;
							break;
						}
					}
					if (!merged) {
						auto it = std::upper_bound(
							next.begin(), next.end(), k,
							[](int v, const std::pair<int, int> &pr) {
								return v < pr.first;
							}
						);
						next.insert(it, {k, 1});
					}
					auto it_node = nodes.find(next);
					auto prev = it_node->second;
					node->next_nodes.insert(prev);
					prev->is_terminate = false;
				}

				if (sum + k + cnt - 2 <= n_ && cnt >= 2) {
					int M = static_cast<int>(node_info_compressed.size());
					for (int i = 0; i < M; ++i) {
						for (int j = i; j < M; ++j) {
							if (i == j && node_info_compressed[i].second < 2)
								continue;

							int len1 = node_info_compressed[i].first;
							int len2 = node_info_compressed[j].first;
							int merged_len = len1 + k + len2;

							auto next = node_info_compressed;

							if (i == j) {
								next[i].second -= 2;
								if (next[i].second == 0)
									next.erase(next.begin() + i);
							} else {
								if (--next[j].second == 0)
									next.erase(next.begin() + j);
								if (--next[i].second == 0)
									next.erase(next.begin() + i);
							}

							bool done = false;
							for (auto &pr: next) {
								if (pr.first == merged_len) {
									pr.second++;
									done = true;
									break;
								}
							}
							if (!done) {
								auto it = std::upper_bound(
									next.begin(), next.end(), merged_len,
									[](int v, auto &pr) { return v < pr.first; }
								);
								next.insert(it, {merged_len, 1});
							}

							auto it_node = nodes.find(next);
							auto prev = it_node->second;
							node->next_nodes.insert(prev);
							//prev->prev_nodes.insert(node);
							prev->is_terminate = false;
						}
					}
				}
			}
		}
	};

	size_t total = node_list.size();
	size_t chunk_size = (total + NUM_THREADS - 1) / NUM_THREADS;
	std::vector<std::thread> threads;

	for (int t = 0; t < NUM_THREADS; ++t) {
		size_t start = t * chunk_size;
		size_t end = std::min(start + chunk_size, total);
		if (start >= end) break;
		threads.emplace_back(worker, start, end, std::cref(node_list));
	}

	for (auto &th: threads) {
		th.join();
	}
}

void RowGraphStrategy::graph::dfs(std::shared_ptr<Node> v, std::vector<std::shared_ptr<Node> > &topsort,
                                  std::unordered_map<std::shared_ptr<Node>, bool> &used) noexcept {
	used[v] = true;

	for (auto u: v->next_nodes) {
		if (used[u]) continue;
		dfs(u, topsort, used);
	}

	topsort.push_back(v);
}

void RowGraphStrategy::graph::calculate_data() noexcept {
	std::unordered_map<std::shared_ptr<Node>, bool> used;
	auto root = nodes[std::vector<std::pair<int, int> >(0)];
	std::vector<std::shared_ptr<Node> > topsort;

	for (auto [node_i, node]: nodes) {
		if (!used[node]) {
			dfs(node, topsort, used);
		}
	}
	std::reverse(topsort.begin(), topsort.end());

	for (auto node: topsort) {
		for (auto nxt: node->next_nodes) {
			if (!nxt->fall_state && !node->fall_state) {
				nxt->fall_state = node;
			}
			if (!nxt->random_state) {
				nxt->random_state = node;
			}
		}
	}
}

bool RowGraphStrategy::graph::is_win(int n) noexcept {
	return static_cast<bool>(nodes[std::vector<std::pair<int, int> >(1, std::make_pair(n, 1))]);
}

RowGraphStrategy::RowGraphStrategy(int n, int k) : Graph(n, k) {
}

RowGraphStrategy::RowGraphStrategy(int n, int a, int b) : Graph(n, a, b) {
}


void RowGraphStrategy::build() noexcept {
	Graph.prepare_nodes();
	Graph.build_graph();
	Graph.calculate_data();
}

std::optional<std::vector<std::pair<int, int> > > RowGraphStrategy::get_next_win_state(
	const std::vector<std::pair<int, int> > &cur_state) noexcept {
	if (!Graph.nodes.count(cur_state)) {
		std::cerr << "WTF: ";
		for (auto [x, y]: cur_state) {
			std::cerr << x << ", " << y << " | ";
		}
		std::cerr << std::endl;
	}
	if (Graph.nodes.count(cur_state) && Graph.nodes[cur_state]->fall_state) {
		return Graph.nodes[cur_state]->fall_state->state;
	}
	return std::nullopt;
}

std::optional<std::vector<int> > RowGraphStrategy::make_transition(const std::vector<bool> &from,
                                                                   const std::vector<std::pair<int, int> > &to)
	noexcept {
	// auto cur_state = iState::get_state_by_field(&from);

	int need_to_delete = std::accumulate(from.begin(), from.end(), 0) - std::accumulate(
		                     to.begin(), to.end(), 0, [](auto ac, auto data) {
			                     return ac + data.first * data.second;
		                     });

	if (need_to_delete < 0) {
		return std::nullopt;
	}

	std::vector<bool> cur_from = from;

	for (int i = 0; i < cur_from.size(); i++) {
		if (i >= need_to_delete) {
			cur_from[i - need_to_delete] = from[i - need_to_delete];
		}
		cur_from[i] = false;
		if (get_state_by_field(&cur_from) == to) {
			std::vector<int> result(need_to_delete);
			iota(result.begin(), result.end(), i - need_to_delete + 1);
			return result;
		}
	}


	return std::nullopt;
}

std::optional<std::vector<int> > RowGraphStrategy::go_win(const std::vector<bool> *field) noexcept {
	auto cur_state = get_state_by_field(field);
	auto next_win_state_opt = get_next_win_state(cur_state);

	if (!next_win_state_opt) {
		return std::nullopt;
	}
	const auto &next_state = next_win_state_opt.value();
	auto moves = make_transition(*field, next_state);
	return moves.value();
}

std::optional<std::vector<int> > RowGraphStrategy::rand_walk(const std::vector<bool> *field) noexcept {
	auto cur_state = get_state_by_field(field);
	if (!Graph.nodes[cur_state]->random_state) {
		return std::nullopt;
	}
	auto next_state = Graph.nodes[cur_state]->random_state->state;
	auto moves = make_transition(*field, next_state);
	return moves.value();
}
