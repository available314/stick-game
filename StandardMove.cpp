//
// Created by pentester on 7/20/25.
//

#include "StandardMove.h"

#include <numeric>

bool StandardMove::check_move(int n, int a, int b, const std::vector<bool> &field, const std::vector<int> &sticks) {
    if (sticks.size() > b || sticks.size() < a) {
        return false;
    }
    for (int i: sticks) {
        if (i >= n || !field[i]) {
            return false;
        }
    }
    return true;
}

bool StandardMove::is_over(int n, int a, int b, const std::vector<bool> &field) {
    int total = std::accumulate(field.begin(), field.end(), 0);
    if (total < a) {
        return true;
    }
    return false;
}

std::string StandardMove::game_rules(int a, int b) {
    return "You can take from " + std::to_string(a) + " to " + std::to_string(b) + " sticks anywhere";
}
