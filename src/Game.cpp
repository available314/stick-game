//
// Created by pentester on 7/18/25.
//

#include "Game.h"

#include <iostream>

Game::Game(int n, int k, std::shared_ptr<iPlayer> first_player, std::shared_ptr<iPlayer> second_player) : Game(n, 1, k, first_player, second_player) {
}

Game::Game(int n, int a, int b, std::shared_ptr<iPlayer> first_player, std::shared_ptr<iPlayer> second_player) : _n(n), _a(a), _b(b), field(n, true) {
    players.first = std::move(first_player);
    players.second = std::move(second_player);
    players.first->setNextPlayer(players.second);
    players.second->setNextPlayer(players.first);

    players.first->setField(&field);
    players.second->setField(&field);
}

void Game::print_field() const {
    std::cout << "Current field:" << std::endl;
    for (auto i : field) {
        if (i) {
            std::cout << "|";
        } else {
            std::cout << ".";
        }
    }
    std::cout << std::endl;
}


void Game::Start() {
    std::cout << "Game started" << std::endl;
    setTurn(players.first);
}


void Game::setStrategy(std::shared_ptr<iBotStrategy> strategy) noexcept {
    this->strategy = std::move(strategy);
}

void Game::setMovesChecker(std::unique_ptr<iCheckMove> checkMove) noexcept {
    this->checkMove = std::move(checkMove);
}


void Game::prepare() const noexcept {
    strategy->build();
}

void Game::setTurn(std::shared_ptr<iPlayer> turn) noexcept {
    current_turn = turn;
    current_turn->setGame(shared_from_this());
}


void Game::playTurn() noexcept {
    print_field();
    std::cout << "Current turn: " << current_turn->getName() << std::endl;
    while (true) {
        auto moves = current_turn->playTurn();

        if (checkMove->check_move(_n, _a, _b, field, moves)) {
            for (const auto i : moves) {
                field[i] = false;
            }
            break;
        }
        for (int i : moves) {
            std::cout << i << ' ';
        }
        std::cout << "Wrong moves!" << std::endl;
    }
}

void Game::nextTurn() noexcept {
    current_turn->nextMove();
}


std::shared_ptr<iBotStrategy> Game::getStrategy() const noexcept {
    return strategy;
}

bool Game::isEnd() const noexcept {
    return strategy->is_over(&field);
}