//
// Created by pentester on 7/19/25.
//


#include "iPlayer.h"

#include <map>

void iPlayer::setGame(std::shared_ptr<Game> game_) noexcept {
    game = std::move(game_);
}

void iPlayer::setField(std::vector<bool> *field_) {
    field = field_;
}

void iPlayer::setNextPlayer(const std::shared_ptr<iPlayer> &nextPlayer_) noexcept {
    nextPlayer = nextPlayer_;
}