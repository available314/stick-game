//
// Created by pentester on 7/18/25.
//

#include "Game.h"

#include <iostream>

Game::Game(std::shared_ptr<iState> first_player, std::shared_ptr<iState> second_player) {
    players.first = std::move(first_player);
    players.second = std::move(second_player);
    players.first->setNextPlayer(players.second);
    players.second->setNextPlayer(players.first);
}

void Game::Start() {
    setTurn(players.first);
}


void Game::setStrategy(std::unique_ptr<iBotStrategy> strategy) noexcept {
    this->strategy = std::move(strategy);
}

void Game::setMovesChecker(std::unique_ptr<iCheckMove> checkMove) noexcept {
    this->checkMove = std::move(checkMove);
}


void Game::prepare() const noexcept {
    strategy->build();
}

void Game::setTurn(std::shared_ptr<iState> turn) noexcept {
    current_turn = turn;
    current_turn->setGame(shared_from_this());
}


void Game::playTurn() noexcept {
    current_turn->playTurn();
}

void Game::nextTurn() noexcept {
    current_turn->nextMove();
}