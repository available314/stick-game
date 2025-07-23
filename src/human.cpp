//
// Created by pentester on 7/19/25.
//

#include "human.h"

#include <iostream>

#include "Game.h"

std::string Human::getName() const noexcept {
    return name;
}

void Human::nextMove() noexcept {
    std::shared_ptr<Game> cur_game = game.lock();
    cur_game->setTurn(nextPlayer.lock());
}

std::optional<std::vector<bool> > Human::prevMove() noexcept {
    if (!backup_fields.empty()) {
        auto res = backup_fields.top();
        backup_fields.pop();
        return res;
    }
    return std::nullopt;
}

void Human::setTurn(const std::vector<int> &moves_) {
    moves = moves_;
}

void Human::save_field(const std::vector<bool> &field) {
    backup_fields.push(field);
}


std::vector<int> Human::playTurn() noexcept {
    return moves;
}
