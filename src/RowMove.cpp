//
// Created by pentester on 7/19/25.
//

#include "RowMove.h"

#include <algorithm>

bool RowMove::check_move(int n, int k, const std::vector<bool> field, std::vector<int> sticks) {
    if (sticks.size() > k || sticks.size() < 1) {
        return false;
    }
    std::sort(sticks.begin(), sticks.end());
    for (int i : sticks) {
        if (!field[i]) {
            return false;
        }
    }
    for (int i = 1; i < sticks.size(); i++) {
        if (sticks[i] != sticks[i - 1] + 1) {
            return false;
        }
    }
    if (sticks.back() >= n) {
        return false;
    }
    return true;
}
