//
// Created by pentester on 7/24/25.
//

#ifndef NORMALMODESTRATEGY_H
#define NORMALMODESTRATEGY_H
#include <unordered_map>
#include <unordered_set>

#include "iBotStrategy.h"

class NormalModeStrategy : public iBotStrategy {
    static constexpr int NUM_THREADS = 12;

    struct graph {
        int n_;

        struct Node {
            int fall_state = -1;
            std::vector<std::pair<int, int> > state;
            std::unordered_set<int> next_states;

            Node() = default;

            Node(const std::vector<std::pair<int, int> > &state_) : state(state_) {
            }
        };

        explicit graph(int n) : n_(n) {
        }

        std::vector<Node> vertex;

        struct VectorPairHash {
            std::size_t operator()(const std::vector<std::pair<int, int> > &vec) const {
                std::size_t h = 0;
                for (const auto &[a, b]: vec) {
                    std::size_t pair_hash = std::hash<int>()(a) ^ (std::hash<int>()(b) << 1);
                    h ^= pair_hash + 0x9e3779b9 + (h << 6) + (h >> 2);
                }
                return h;
            }
        };

        std::unordered_map<std::vector<std::pair<int, int> >, int, VectorPairHash> vertex_idx;


        std::vector<std::pair<int, int> > compress(const std::vector<int> &node_info) noexcept;

        void brute_nodes(int n, int k, std::vector<std::vector<std::pair<int, int> > > &result, int lst = 1) noexcept;

        void prepare_nodes() noexcept;

        void build_graph() noexcept;

        std::vector<std::vector<std::pair<int, int> > > add_k_sequence(
            const std::vector<std::pair<int, int> > &cur_state,
            int k) noexcept;

        void dfs(int v, std::vector<int> &topsort,
                 std::vector<bool> &used) noexcept;

        void calculate_data() noexcept;

        bool try_to_read_from_file() noexcept;
    };

    graph Graph;
    int n_;


    std::optional<std::vector<std::pair<int, int> > > get_next_win_state(
        const std::vector<std::pair<int, int> > &cur_state) noexcept;

    std::optional<std::vector<int> > make_transition(const std::vector<bool> &from,
                                                     const std::vector<std::pair<int, int> > &to)
        noexcept;

public:
    explicit NormalModeStrategy(int n);

    void build() override;

    std::optional<std::vector<int> > go_win(const std::vector<bool> *state) noexcept override;

    std::optional<std::vector<int> > rand_walk(const std::vector<bool> *state) noexcept override;


    ~NormalModeStrategy() override = default;
};

#endif //NORMALMODESTRATEGY_H
