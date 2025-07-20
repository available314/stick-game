//
// Created by pentester on 7/20/25.
//

#ifndef BOT_H
#define BOT_H

#include "iPlayer.h"

class Bot final : public iPlayer {
    const std::string name;



public:
    explicit Bot(const std::string &name_) noexcept;

    std::string getName() const noexcept override;
    void nextMove() noexcept override;
    void prevMove() noexcept override;
    std::vector<int> playTurn() override;

    ~Bot() noexcept override = default;
};

#endif //BOT_H
