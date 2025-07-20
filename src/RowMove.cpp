//
// Created by pentester on 7/19/25.
//

#include "RowMove.h"

#include <algorithm>

bool RowMove::check_move(int n, int a, int b, const std::vector<bool> field, std::vector<int> sticks) {
    if (sticks.size() > b || sticks.size() < a) {
        return false;
    }
    std::sort(sticks.begin(), sticks.end());
    for (int i : sticks) {
        if (i >= n || !field[i]) {
            return false;
        }
    }
    for (int i = 1; i < sticks.size(); i++) {
        if (sticks[i] != sticks[i - 1] + 1) {
            return false;
        }
    }
    return true;
}
