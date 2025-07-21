//
// Created by pentester on 7/18/25.
//

#include "Game.h"

#include <iostream>

Game::Game(int n, int k, std::shared_ptr<iPlayer> first_player, std::shared_ptr<iPlayer> second_player) : Game(
    n, 1, k, first_player, second_player) {
}

Game::Game(int n, int a, int b, std::shared_ptr<iPlayer> first_player,
           std::shared_ptr<iPlayer> second_player) : _n(n), _a(a), _b(b), field(n, true) {
    players.first = std::move(first_player);
    players.second = std::move(second_player);
    players.first->setNextPlayer(players.second);
    players.second->setNextPlayer(players.first);

    players.first->setField(&field);
    players.second->setField(&field);
}

void Game::prepare_players() noexcept {
    players.first->setGame(shared_from_this());
    players.second->setGame(shared_from_this());
}

void Game::print_field() const {
    std::cout << "Current field:" << std::endl;
    for (auto i: field) {
        if (i) {
            std::cout << "|";
        } else {
            std::cout << ".";
        }
    }
    std::cout << std::endl;
}


void Game::Start() {
    prepare_players();
    std::cout << "Game started" << std::endl;
    setTurn(players.first);
    std::cout << " exit" << std::endl;
}


void Game::setStrategyForFirstPlayer(std::unique_ptr<iBotStrategy> strategy) const noexcept {
    players.first->setStrategy(std::move(strategy));
}

void Game::setStrategyForSecondPlayer(std::unique_ptr<iBotStrategy> strategy) const noexcept {
    players.second->setStrategy(std::move(strategy));
}

void Game::setMovesChecker(std::unique_ptr<iCheckMove> checkMove) noexcept {
    this->checkMove = std::move(checkMove);
}

void Game::setTurn(std::shared_ptr<iPlayer> turn) noexcept {
    current_turn = turn;
}


void Game::playTurn() noexcept {
    print_field();
    std::cout << "Current turn: " << current_turn->getName() << std::endl;
    while (true) {
        auto moves = current_turn->playTurn();

        if (checkMove->check_move(_n, _a, _b, field, moves)) {
            for (const auto i: moves) {
                field[i] = false;
            }
            break;
        }
        for (int i: moves) {
            std::cout << i << ' ';
        }
        std::cout << "Wrong moves!" << std::endl;
    }
}

void Game::nextTurn() noexcept {
    current_turn->nextMove();
}

bool Game::isEnd() const noexcept {
    return checkMove->is_over(_n, _a, _b, field);
}

std::string Game::loser() const noexcept {
    if (!isEnd()) {
        return "in process";
    }
    return current_turn->getName();
}
