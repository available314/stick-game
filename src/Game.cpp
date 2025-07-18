//
// Created by pentester on 7/18/25.
//

#include "Game.h"

void Game::setStrategy(std::unique_ptr<iBotStrategy> strategy) noexcept {
    this->strategy = std::move(strategy);
}

void Game::setMovesChecker(std::unique_ptr<iCheckMove> checkMove) noexcept {
    this->checkMove = std::move(checkMove);
}


void Game::prepare() noexcept {
    strategy->build();
}