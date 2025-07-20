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

void Human::prevMove() noexcept {

}


std::vector<int> Human::playTurn() noexcept {
    std::cout << "Current turn: " << name << std::endl;
    std::cout << "Enter moves: " << std::endl;

    int n;
    std::cin >> n;

    std::vector<int> moves(n);
    for (int i = 0; i < n; i++) {
        std::cin >> moves[i];
    }

    return moves;
}