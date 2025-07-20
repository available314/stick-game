//
// Created by pentester on 7/20/25.
//

#include "StandardMove.h"

bool StandardMove::check_move(int n, int a, int b, const std::vector<bool> field, const std::vector<int> sticks) {
    if (sticks.size() > b || sticks.size() < a) {
        return false;
    }
    for (int i : sticks) {
        if (i >= n || !field[i]) {
            return false;
        }
    }
    return true;
}
