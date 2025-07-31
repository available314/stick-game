//
// Created by pentester on 7/19/25.
//

#ifndef ROWMOVE_H
#define ROWMOVE_H

#include "iCheckMove.h"

class RowMove : public iCheckMove {
public:
    RowMove() = default;

    bool check_move(int n, int a, int b, const std::vector<bool> &field, const std::vector<int> &sticks) override;

    bool is_over(int n, int a, int b, const std::vector<bool> &field) override;

    std::string game_rules(int a, int b) override;

    ~RowMove() = default;
};

#endif //ROWMOVE_H
