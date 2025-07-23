//
// Created by pentester on 7/19/25.
//

#ifndef HUMAN_H
#define HUMAN_H

#include "iPlayer.h"

#include <string>
#include <memory>
#include <stack>

class Human : public iPlayer {
    const std::string name;
    std::vector<int> moves;

    std::stack<std::vector<bool> > backup_fields;

public:
    explicit Human(const std::string &_name) : name(_name) {
    }

    void nextMove() noexcept override;

    std::optional<std::vector<bool> > prevMove() noexcept override;

    std::string getName() const noexcept override;

    void save_field(const std::vector<bool> &field);

    void setTurn(const std::vector<int> &moves);

    std::vector<int> playTurn() noexcept override;

    ~Human() override = default;
};

#endif //HUMAN_H
