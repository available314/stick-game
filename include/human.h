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

public:
    explicit Human(const std::string &_name) : name(_name) {}

    void nextMove() noexcept override;
    void prevMove() noexcept override;

    std::string getName() const noexcept override;
    void playTurn() noexcept override;

    ~Human() override = default;
};

#endif //HUMAN_H
