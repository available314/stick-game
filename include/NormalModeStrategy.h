//
// Created by pentester on 7/24/25.
//

#ifndef NORMALMODESTRATEGY_H
#define NORMALMODESTRATEGY_H
#include <unordered_map>

#include "iBotStrategy.h"

class NormalModeStrategy : public iBotStrategy {
    struct graph {
        int n_;

        struct Node {
            int random_state = -1;
            int fall_state = -1;
            std::vector<std::pair<int, int> > state;
            std::vector<int> next_state;

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

        void dfs(int v, std::vector<int> &topsort,
                 std::vector<int> &used) noexcept;

        void calculate_data() noexcept;

        bool is_win(int n) noexcept;
    };

public:
    explicit NormalModeStrategy(int n);

    void build() override;

    bool is_over(const std::vector<bool> *field) noexcept override;

    std::optional<std::vector<int> > go_win(const std::vector<bool> *state) noexcept override;

    std::optional<std::vector<int> > rand_walk(const std::vector<bool> *state) noexcept override;


    ~NormalModeStrategy() override = default;
};

#endif //NORMALMODESTRATEGY_H
