//
// Created by pentester on 7/19/25.
//

#include "RowMove.h"

#include <algorithm>

bool RowMove::check_move(int n, int a, int b, const std::vector<bool> &field, const std::vector<int> &sticks_) {
    auto sticks = sticks_;

    if (sticks.size() > b || sticks.size() < a) {
        return false;
    }
    std::sort(sticks.begin(), sticks.end());
    for (int i: sticks) {
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

bool RowMove::is_over(int n, int a, int b, const std::vector<bool> &field) {
    int len = 0;

    for (int i = 0; i < n; i++) {
        if (field[i]) {
            len++;
        } else {
            len = 0;
        }
        if (len >= a) {
            return false;
        }
    }

    return true;
}

std::string RowMove::game_rules(int a, int b) {
    return "You can take from " + std::to_string(a) + " to " + std::to_string(b) + " sticks in a row";
}
