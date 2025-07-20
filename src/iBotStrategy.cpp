//
// Created by pentester on 7/20/25.
//

#include "iBotStrategy.h"

#include <map>
#include <stdexcept>

std::vector<std::pair<int, int>> iBotStrategy::get_state_by_field(const std::vector<bool> *state) noexcept {
    std::map<int, int> len_cnt;

    int cur_len = 0;
    for (int i = 0; i < state->size(); i++) {
        if (state->at(i)) {
            cur_len++;
        } else {
            if (cur_len) {
                len_cnt[cur_len]++;
            }
            cur_len = 0;
        }
    }
    if (cur_len) {
        len_cnt[cur_len]++;
    }
    std::vector<std::pair<int, int>> ret;
    for (auto res : len_cnt) {
        ret.push_back(res);
    }
    return ret;
}

std::vector<int> iBotStrategy::do_turn(const std::vector<bool> *state) {
    auto result = go_win(state);

    if (!result) {
        result = rand_walk(state);
    }

    if (!result) {
        throw std::runtime_error("Couldnt find any moves!!");
    }
    return result.value();
}