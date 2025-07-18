//
// Created by pentester on 7/18/25.
//

#ifndef ROWSTRATEGY_H
#define ROWSTRATEGY_H

#include <cstddef>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "iBotStrategy.h"

class RowStrategy final : public iBotStrategy {

    struct graph {
        const int NUM_THREADS = 12;
        int n_, a_, b_;

        graph(int _n, int _k) : n_(_n), a_(1), b_(_k) {}
        graph(int _n, int _a, int _b) : n_(_n), a_(_a), b_(_b) {}

        struct Node {
            std::unordered_set<std::shared_ptr<Node>> next_nodes;
            std::shared_ptr<Node> fall_state;

            Node () = default;
        };

        struct VectorPairHash {
            std::size_t operator()(const std::vector<std::pair<int, int>>& vec) const {
                std::size_t h = 0;
                for (const auto& [a, b] : vec) {
                    std::size_t pair_hash = std::hash<int>()(a) ^ (std::hash<int>()(b) << 1);
                    h ^= pair_hash + 0x9e3779b9 + (h << 6) + (h >> 2);
                }
                return h;
            }
        };

        std::unordered_map<std::vector<std::pair<int, int>>, std::shared_ptr<Node>, VectorPairHash> nodes;

        std::vector<std::pair<int, int>> compress(const std::vector<int> &node_info) noexcept;
        void brute_nodes(int n, int k, std::vector<std::vector<std::pair<int, int>>> &result, int lst = 1) noexcept;
        void prepare_nodes() noexcept;
        void build_graph() noexcept;
        void dfs(std::shared_ptr<Node> v, std::vector<std::shared_ptr<Node>> &topsort, std::unordered_map<std::shared_ptr<Node>, bool> &used) noexcept;
        void calculate_data() noexcept;
        bool is_win(int n) noexcept;
    } Graph;

public:

    explicit RowStrategy(int n, int k);
    explicit RowStrategy(int n, int a, int b);

    void build() override;

    ~RowStrategy() override = default;
};

#endif //ROWSTRATEGY_H
