//
// Created by pentester on 7/19/25.
//

#ifndef HUMAN_H
#define HUMAN_H

#include "iPlayer.h"

#include <string>
#include <memory>

class Human : public iPlayer {
    const std::string name;
    std::vector<int> moves;

public:
    explicit Human(const std::string &_name) : name(_name) {
    }

    void nextMove() noexcept override;

    void prevMove() noexcept override;

    std::string getName() const noexcept override;

    void setTurn(const std::vector<int> &moves);

    std::vector<int> playTurn() noexcept override;

    ~Human() override = default;
};

#endif //HUMAN_H
