//
// Created by pentester on 7/20/25.
//

#include "bot.h"
#include "Game.h"

#include <stdexcept>


Bot::Bot(const std::string &name_) noexcept : name(name_) {
}


std::string Bot::getName() const noexcept {
    return name;
}

void Bot::nextMove() noexcept {
    std::shared_ptr<Game> cur_game = game.lock();
    cur_game->setTurn(nextPlayer.lock());
}


std::optional<std::vector<bool> > Bot::prevMove() noexcept {
    return std::nullopt;
}


std::vector<int> Bot::playTurn() {
    if (!strategy) {
        throw std::runtime_error("Not a valid strategy for bot");
    }

    auto win_moves = strategy->do_turn(field);

    return win_moves;
}
