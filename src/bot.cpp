//
// Created by pentester on 7/20/25.
//

#include "bot.h"
#include "Game.h"


Bot::Bot(const std::string &name_) noexcept : name(name_) {}


std::string Bot::getName() const noexcept {
    return name;
}

void Bot::nextMove() noexcept {
    std::shared_ptr<Game> cur_game = game.lock();
    cur_game->setTurn(nextPlayer.lock());
}


void Bot::prevMove() noexcept {

}



std::vector<int> Bot::playTurn() {
    std::shared_ptr<Game> cur_game = game.lock();
    auto strategy = cur_game->getStrategy();

    auto win_moves = strategy->do_turn(field);

    return win_moves;
}