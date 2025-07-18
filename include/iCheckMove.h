//
// Created by pentester on 7/19/25.
//

#ifndef ICHECKMOVE_H
#define ICHECKMOVE_H

#include <vector>

class iCheckMove {
public:
    iCheckMove() = default;

    virtual bool check_move(int k, const std::vector<bool> field, const std::vector<int> sticks) = 0;

    virtual ~iCheckMove() = default;
};

#endif //ICHECKMOVE_H
