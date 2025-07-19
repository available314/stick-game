//
// Created by pentester on 7/19/25.
//

#ifndef ROWMOVE_H
#define ROWMOVE_H

#include "iCheckMove.h"

class RowMove : public iCheckMove {
    public:
    RowMove() = default;

    bool check_move(int k, const std::vector<bool> field, const std::vector<int> sticks) override;

    ~RowMove() override = default;
};

#endif //ROWMOVE_H
