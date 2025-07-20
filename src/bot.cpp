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


    auto cur_state = iState::get_state_by_field(field);

    auto next_win_state_opt = strategy->get_next_win_state(cur_state);

    if (!next_win_state_opt) { // ToDo: better handler
        for (int i = 0; i < field->size(); i++) {
            if (field->at(i)) {
                return std::vector<int>(1, i);
            }
        }
    }
    auto next_state = next_win_state_opt.value();
    auto moves = strategy->make_transition(*field, next_state);
    if (!moves) {
        throw std::runtime_error("No moves left");
    }


    return moves.value();
}