//
// Created by pentester on 7/21/25.
//

#include "RowGrundyStrategy.h"

#include <numeric>
#include <unordered_set>

RowGrundyStrategy::RowGrundyStrategy(int _n, int _a, int _b) noexcept : n_(_n), a_(_a), b_(_b) {
    grundy.resize(n_ + 1);
}

RowGrundyStrategy::RowGrundyStrategy(int _n, int _k) noexcept : RowGrundyStrategy(_n, 1, _k) {
}


void RowGrundyStrategy::compute_grundy() noexcept {
    for (int len = 1; len <= n_; ++len) {
        std::unordered_set<int> gset;
        for (int take = a_; take <= b_; ++take) {
            if (take > len) break;
            for (int i = 0; i + take <= len; ++i) {
                int left = i;
                int right = len - i - take;
                gset.insert(grundy[left] ^ grundy[right]);
            }
        }
        int mex = 0;
        while (gset.count(mex)) {
            mex++;
        }
        grundy[len] = mex;
    }
}

int RowGrundyStrategy::compute_field_grundy(const std::vector<bool> &field) const noexcept {
    int g = 0;
    int len = 0;
    for (bool has: field) {
        if (has) {
            ++len;
        } else if (len > 0) {
            g ^= grundy[len];
            len = 0;
        }
    }
    if (len > 0) {
        g ^= grundy[len];
    }
    return g;
}


void RowGrundyStrategy::build() noexcept {
    compute_grundy();
}

std::optional<std::vector<int> > RowGrundyStrategy::go_win(const std::vector<bool> *state) noexcept {
    const auto &field = *state;
    int current_grundy = compute_field_grundy(field);

    if (current_grundy == 0) {
        return std::nullopt;
    }

    for (int i = 0; i <= n_ - a_; ++i) {
        for (int len = a_; len <= b_ && i + len <= n_; ++len) {
            bool valid = true;
            for (int j = i; j < i + len; ++j) {
                if (!field[j]) {
                    valid = false;
                    break;
                }
            }
            if (!valid) continue;

            std::vector<bool> next = field;
            for (int j = i; j < i + len; ++j) {
                next[j] = false;
            }

            if (compute_field_grundy(next) == 0) {
                std::vector<int> result;
                for (int j = i; j < i + len; ++j) result.push_back(j);
                return result;
            }
        }
    }
    return std::nullopt;
}

std::optional<std::vector<int> > RowGrundyStrategy::rand_walk(const std::vector<bool> *state) noexcept {
    int len = 0;
    for (int i = 0; i < n_; i++) {
        if (state->at(i)) {
            len++;
        } else {
            len = 0;
        }
        if (len == a_) {
            std::vector<int> moves(a_);
            std::iota(moves.begin(), moves.end(), i - a_ + 1);
            return moves;
        }
    }

    return std::nullopt;
}


