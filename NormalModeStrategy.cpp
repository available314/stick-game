//
// Created by pentester on 7/24/25.
//

#include "NormalModeStrategy.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <thread>

std::vector<std::pair<int, int> > NormalModeStrategy::graph::compress(const std::vector<int> &node_info) noexcept {
	std::vector<std::pair<int, int> > node_info_compressed;

	for (int i = 0; i < node_info.size(); i++) {
		if (!node_info_compressed.size() || node_info_compressed.back().first != node_info[i]) {
			node_info_compressed.emplace_back(node_info[i], 0);
		}
		node_info_compressed.back().second++;
	}
	return node_info_compressed;
}

void NormalModeStrategy::graph::brute_nodes(int n, int k, std::vector<std::vector<std::pair<int, int> > > &result,
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

void NormalModeStrategy::graph::prepare_nodes() noexcept {
	vertex.reserve(239943 + 5);
	vertex.emplace_back(std::vector<std::pair<int, int> >(0));
	vertex_idx[vertex[0].state] = 0;
	// root node

	for (int i = 1; i <= n_; i++) {
		std::vector<std::vector<std::pair<int, int> > > result;
		brute_nodes(n_ - i + 1, i, result);

		for (const auto &pairs: result) {
			vertex.emplace_back(pairs);
			vertex_idx[vertex.back().state] = vertex.size() - 1;
		}
	}
}

std::vector<std::vector<std::pair<int, int> > > NormalModeStrategy::graph::add_k_sequence(
	const std::vector<std::pair<int, int> > &node_info_compressed,
	int k) noexcept {
	std::vector<std::vector<std::pair<int, int> > > result;

	auto [sum, cnt] = std::accumulate(node_info_compressed.begin(), node_info_compressed.end(),
	                                  std::make_pair(0, 0),
	                                  [](std::pair<int, int> ac, std::pair<int, int> cur) {
		                                  return std::make_pair(ac.first + cur.first * cur.second,
		                                                        ac.second + cur.second);
	                                  });


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
			result.push_back(cur);
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
		result.push_back(next);
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

				result.push_back(next);
			}
		}
	}

	return result;
}


void NormalModeStrategy::graph::build_graph() noexcept {
	auto worker = [n_ = this->n_, &vertex_idx = this->vertex_idx, &vertex = this->vertex, this](
		size_t start, size_t end) {
		for (size_t i = start; i < end; i++) {
			auto res = add_k_sequence(vertex[i].state, 1);

			for (const auto &state: res) {
				vertex[i].next_states.insert(vertex_idx[state]);
				auto added_two_sticks = add_k_sequence(state, 1);
				for (const auto &state_two: added_two_sticks) {
					vertex[i].next_states.insert(vertex_idx[state_two]);
				}
			}
			res = add_k_sequence(vertex[i].state, 3);
			for (const auto &state: res) {
				vertex[i].next_states.insert(vertex_idx[state]);
			}
		}
	};

	size_t total = vertex.size();
	size_t chunk_size = (total + NUM_THREADS - 1) / NUM_THREADS;
	std::vector<std::thread> threads;

	for (int t = 0; t < NUM_THREADS; ++t) {
		size_t start = t * chunk_size;
		size_t end = std::min(start + chunk_size, total);
		if (start >= end) break;
		threads.emplace_back(worker, start, end);
	}

	for (auto &th: threads) {
		th.join();
	}
}

void NormalModeStrategy::graph::dfs(int v, std::vector<int> &topsort,
                                    std::vector<bool> &used) noexcept {
	used[v] = true;

	for (auto u: vertex[v].next_states) {
		if (used[u]) continue;
		dfs(u, topsort, used);
	}

	topsort.push_back(v);
}

void NormalModeStrategy::graph::calculate_data() noexcept {
	std::vector<bool> used(vertex.size());
	std::vector<int> topsort;

	for (auto [node_i, node_idx
	     ]: vertex_idx) {
		if (!used[node_idx]) {
			dfs(node_idx, topsort, used);
		}
	}
	std::reverse(topsort.begin(), topsort.end());

	for (auto node: topsort) {
		for (auto nxt: vertex[node].next_states) {
			if (vertex[nxt].fall_state == -1 && vertex[node].fall_state == -1) {
				vertex[nxt].fall_state = node;
			}
		}
	}

	std::ofstream cache_file("cache.txt");

	cache_file << vertex.size() << std::endl;

	for (size_t node = 0; node < vertex.size(); node++) {
		cache_file << node << ' ' << vertex[node].fall_state << ' ' << vertex[node].
				state.size();
		for (auto [x, y]: vertex[node].state) {
			cache_file << ' ' << x << ' ' << y;
		}
		cache_file << std::endl;
	}
}

bool NormalModeStrategy::graph::try_to_read_from_file() noexcept {
	std::fstream cache_file("cache.txt");

	int n;
	if (!(cache_file >> n)) return false;

	if (n != 239943) return false;
	vertex.resize(n);

	for (int i = 0; i < n; i++) {
		int vertex_id, fall_state_id, state_k;
		cache_file >> vertex_id >> fall_state_id >> state_k;
		std::vector<std::pair<int, int> > his_state(state_k);
		for (auto &[x, y]: his_state) {
			cache_file >> x >> y;
		}
		vertex[vertex_id] = Node(his_state);
		vertex_idx[his_state] = vertex_id;

		vertex[vertex_id].fall_state = fall_state_id;
	}

	return true;
}

NormalModeStrategy::NormalModeStrategy(int n) : Graph(n), n_(n) {
}

void NormalModeStrategy::build() {
	if (!Graph.try_to_read_from_file()) {
		Graph.prepare_nodes();
		Graph.build_graph();
		Graph.calculate_data();
	}
}

std::optional<std::vector<std::pair<int, int> > > NormalModeStrategy::get_next_win_state(
	const std::vector<std::pair<int, int> > &cur_state) noexcept {
	if (Graph.vertex_idx.count(cur_state) && Graph.vertex[Graph.vertex_idx[cur_state]].fall_state != -1) {
		return Graph.vertex[Graph.vertex[Graph.vertex_idx[cur_state]].fall_state].state;
	}
	return std::nullopt;
}

std::optional<std::vector<int> > NormalModeStrategy::make_transition(const std::vector<bool> &from,
                                                                     const std::vector<std::pair<int, int> > &to)
	noexcept {
	auto cur_field = from;

	auto need_to_delete = std::accumulate(from.begin(), from.end(), 0) - std::accumulate(
		                      to.begin(), to.end(), 0, [](int ac, std::pair<int, int> cx) {
			                      return ac + cx.first * cx.second;
		                      });

	if (need_to_delete == 1) {
		for (int i = 0; i < from.size(); i++) {
			if (from[i]) {
				cur_field[i] = false;
				if (get_state_by_field(&cur_field) == to) {
					return std::vector<int>(1, i);
				}
				cur_field[i] = true;
			}
		}
	} else if (need_to_delete == 2) {
		for (int i = 0; i < from.size(); i++) {
			if (from[i]) {
				cur_field[i] = false;
				for (int j = i + 1; j < from.size(); j++) {
					if (from[j]) {
						cur_field[j] = false;
						if (get_state_by_field(&cur_field) == to) {
							return std::vector{i, j};
						}
						cur_field[j] = true;
					}
				}
				cur_field[i] = true;
			}
		}
	} else if (need_to_delete == 3) {
		for (int i = 0; i + 3 <= from.size(); i++) {
			if (cur_field[i] && cur_field[i + 1] && cur_field[i + 2]) {
				cur_field[i] = cur_field[i + 1] = cur_field[i + 2] = false;

				if (get_state_by_field(&cur_field) == to) {
					return std::vector{i, i + 1, i + 2};
				}
				cur_field[i] = cur_field[i + 1] = cur_field[i + 2] = true;
			}
		}
	}

	return std::nullopt;
}

std::optional<std::vector<int> > NormalModeStrategy::go_win(const std::vector<bool> *field) noexcept {
	auto cur_state = get_state_by_field(field);
	auto next_win_state_opt = get_next_win_state(cur_state);

	if (!next_win_state_opt) {
		return std::nullopt;
	}
	const auto &next_state = next_win_state_opt.value();
	auto moves = make_transition(*field, next_state);
	return moves.value();
}


std::optional<std::vector<int> > NormalModeStrategy::rand_walk(const std::vector<bool> *field) noexcept {
	std::vector<int> result;
	for (size_t i = 0; i < field->size(); i++) {
		if (field->at(i)) {
			result.push_back(i);
			return result;
		}
	}
	return std::nullopt;
}
