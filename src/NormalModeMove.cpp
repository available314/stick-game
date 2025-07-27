//
// Created by pentester on 7/25/25.
//


#include "NormalModeMove.h"

#include <algorithm>
#include <numeric>

bool NormalModeMove::check_move(int n, int a, int b, const std::vector<bool> &field, const std::vector<int> &sticks_) {
    std::vector<int> sticks = sticks_;
    if (sticks.size() > 3 || sticks.size() < 1) {
        return false;
    }

    for (int i: sticks) {
        if (i >= n || !field[i]) {
            return false;
        }
    }
    if (sticks.size() == 3) {
        std::sort(sticks.begin(), sticks.end());
        if (sticks[0] + 1 != sticks[1] || sticks[1] + 1 != sticks[2]) {
            return false;
        }
    }
    return true;
}

bool NormalModeMove::is_over(int n, int a, int b, const std::vector<bool> &field) {
    int sum = std::accumulate(field.begin(), field.end(), 0);
    if (sum < 1) {
        return true;
    }
    return false;
}

std::string NormalModeMove::game_rules(int a, int b) {
    return R"(You can take 1 or 2 sticks anywhere or 3 in row)";
}
