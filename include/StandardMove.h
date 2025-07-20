//
// Created by pentester on 7/20/25.
//

#ifndef STANDARDMOVE_H
#define STANDARDMOVE_H
#include "iCheckMove.h"

class StandardMove : public iCheckMove {
public:
    StandardMove() = default;

    bool check_move(int n, int a, int b, const std::vector<bool> field, const std::vector<int> sticks) override;

    ~StandardMove() override = default;
};

#endif //STANDARDMOVE_H
