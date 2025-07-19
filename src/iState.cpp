//
// Created by pentester on 7/19/25.
//


#include "iState.h"

void iState::setGame(std::shared_ptr<Game> game_) noexcept {
    game = std::move(game_);
}

void iState::setField(const std::vector<bool> &field_) {
    field = field_;
}

void iState::setNextPlayer(std::shared_ptr<iState> nextPlayer_) noexcept {
    nextPlayer = nextPlayer_;
}