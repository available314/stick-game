//
// Created by pentester on 7/25/25.
//


#include "NormalModeMove.h"

#include <algorithm>
#include <numeric>

bool NormalModeMove::check_move(int n, int a, int b, const std::vector<bool> &field, const std::vector<int> &sticks) {
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
    int sum = std::std::accumulate(field.begin(), field.end(), 0);
    if (sum < 1) {
        return true;
    }
    return false;
}
