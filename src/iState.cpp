//
// Created by pentester on 7/19/25.
//


#include "iState.h"

#include <map>

void iState::setGame(std::shared_ptr<Game> game_) noexcept {
    game = std::move(game_);
}

void iState::setField(std::vector<bool> *field_) {
    field = field_;
}

void iState::setNextPlayer(const std::shared_ptr<iState> &nextPlayer_) noexcept {
    nextPlayer = nextPlayer_;
}

std::vector<std::pair<int, int>> iState::get_state_by_field(const std::vector<bool> *state) noexcept {
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