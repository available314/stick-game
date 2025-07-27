//
// Created by pentester on 7/19/25.
//

#ifndef ICHECKMOVE_H
#define ICHECKMOVE_H

#include <string>
#include <vector>

class iCheckMove {
public:
    iCheckMove() = default;

    virtual bool check_move(int n, int a, int b, const std::vector<bool> &field, const std::vector<int> &sticks) = 0;

    virtual bool is_over(int n, int a, int b, const std::vector<bool> &field) = 0;

    virtual std::string game_rules(int a, int b) = 0;

    ~iCheckMove() = default;
};

#endif //ICHECKMOVE_H
