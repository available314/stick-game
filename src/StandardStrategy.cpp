//
// Created by pentester on 7/20/25.
//

#include <numeric>

#include "StandardStrategy.h"

StandardStrategy::StandardStrategy(int n, int a, int b) : _n(n), _a(a), _b(b) {
    failure_state.assign(_n + 1, -1);
}

StandardStrategy::StandardStrategy(int n, int k) : StandardStrategy(n, 1, k) {
}

void StandardStrategy::build() noexcept {
    for (int i = 0; i <= _n; i++) {
        int res = -1;
        for (int j = _a; j <= _b; j++) {
            if (i >= j && failure_state[i - j] == -1) {
                res = i - j;
            }
        }
        failure_state[i] = res;
    }
}

std::optional<std::vector<int> > StandardStrategy::go_win(const std::vector<bool> *state) noexcept {
    auto sum = std::accumulate(state->begin(), state->end(), 0);

    if (failure_state[sum] == -1) {
        return std::nullopt;
    }

    int to_take = sum - failure_state[sum];
    std::vector<int> result;
    result.reserve(to_take);
    for (int i = 0; i < state->size() && result.size() < to_take; i++) {
        if (state->at(i)) {
            result.push_back(i);
        }
    }
    return result;
}

std::optional<std::vector<int> > StandardStrategy::rand_walk(const std::vector<bool> *state) noexcept {
    std::vector<int> result;
    result.reserve(_a);

    for (int i = 0; i < state->size() && result.size() < _a; i++) {
        if (state->at(i)) {
            result.push_back(i);
        }
    }
    return result;
}
