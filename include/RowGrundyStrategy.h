//
// Created by pentester on 7/21/25.
//

#ifndef ROWGRUNDYBOT_H
#define ROWGRUNDYBOT_H
#include "iBotStrategy.h"

class RowGrundyStrategy final : public iBotStrategy {
    int n_, a_, b_;
    std::vector<int> grundy;

    void compute_grundy() noexcept;

    int compute_field_grundy(const std::vector<bool> &field) const noexcept;

public:
    RowGrundyStrategy(int _n, int _k) noexcept;

    RowGrundyStrategy(int _n, int _a, int _b) noexcept;

    void build() noexcept override;

    std::optional<std::vector<int> > go_win(const std::vector<bool> *state) noexcept override;

    std::optional<std::vector<int> > rand_walk(const std::vector<bool> *state) noexcept override;

    ~RowGrundyStrategy() override = default;
};

#endif //ROWGRUNDYBOT_H
