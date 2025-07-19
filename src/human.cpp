//
// Created by pentester on 7/19/25.
//

#include "human.h"

#include "Game.h"

void Human::nextMove() noexcept {
    std::shared_ptr<Game> cur_game = game.lock();
    cur_game->setTurn(nextPlayer.lock());
}

void Human::prevMove() noexcept {

}