//
// Created by pentester on 7/19/25.
//

#ifndef HUMAN_H
#define HUMAN_H

#include "iState.h"

#include <string>
#include <memory>

class Human : public iState {
    const std::string name;

    std::shared_ptr<iState> nextPlayer;

public:
    Human(const std::string &_name, const std::shared_ptr<iState> &nextPlayer_) : name(_name), nextPlayer(nextPlayer_) {}

    void nextMove() noexcept override;

    ~Human() override = default;
};

#endif //HUMAN_H
