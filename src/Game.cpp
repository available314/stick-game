//
// Created by pentester on 7/18/25.
//

#include "Game.h"

#include <iostream>

#include "bot.h"
#include "human.h"

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
    setTurn(players.first);
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

bool Game::playTurn() noexcept {
    auto moves = current_turn->playTurn();

    if (checkMove->check_move(_n, _a, _b, field, moves)) {
        if (isCurrentPlayerHuman()) {
            static_cast<Human *>(current_turn.get())->save_field(field);
        }
        for (const auto i: moves) {
            field[i] = false;
        }
        return true;
    }
    return false;
}

void Game::nextTurn() noexcept {
    current_turn->nextMove();
}

bool Game::undoStep() noexcept {
    if (dynamic_cast<Human *>(current_turn.get()) == nullptr) {
        return false;
    }
    if (auto res = current_turn->prevMove()) {
        field = res.value();
        return true;
    }
    return false;
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

std::string Game::getCurrentPlayerName() const noexcept {
    return current_turn->getName();
}

const std::vector<bool> &Game::getField() const noexcept {
    return field;
}

bool Game::isCurrentPlayerBot() const noexcept {
    return dynamic_cast<Bot *>(current_turn.get()) != nullptr;
}

bool Game::isCurrentPlayerHuman() const noexcept {
    return dynamic_cast<Human *>(current_turn.get()) != nullptr;
}

bool Game::setHumanTurn(const std::vector<int> &moves) {
    auto human = dynamic_cast<Human *>(current_turn.get());
    if (!human) {
        throw std::runtime_error("Human turn is not currently available");
    }
    human->setTurn(moves);
    return playTurn();
}

std::string Game::game_rule() const {
    return checkMove->game_rules(_a, _b);
}
