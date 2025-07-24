//
// Created by pentester on 7/25/25.
//

#ifndef NORMALMODEMOVE_H
#define NORMALMODEMOVE_H
#include "iCheckMove.h"

class NormalModeMove : public iCheckMove {
public:
    NormalModeMove() = default;

    bool check_move(int n, int a, int b, const std::vector<bool> &field, const std::vector<int> &sticks) override;

    bool is_over(int n, int a, int b, const std::vector<bool> &field) override;

    ~NormalModeMove() override = default;
};

#endif //NORMALMODEMOVE_H
