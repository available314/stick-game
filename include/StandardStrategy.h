//
// Created by pentester on 7/20/25.
//

#ifndef STRANDARDSTRATEGY_H
#define STRANDARDSTRATEGY_H
#include "iBotStrategy.h"

class StandardStrategy final : public iBotStrategy {
    int _n, _a, _b;

    std::vector<int> failure_state;

public:
    explicit StandardStrategy(int n, int k);

    explicit StandardStrategy(int n, int a, int b);

    void build() noexcept override;

    std::optional<std::vector<int> > go_win(const std::vector<bool> *state) noexcept override;

    std::optional<std::vector<int> > rand_walk(const std::vector<bool> *state) noexcept override;

    ~StandardStrategy() override = default;
};

#endif //STRANDARDSTRATEGY_H
