//
// Created by pentester on 7/19/25.
//

#ifndef ISTATE_H
#define ISTATE_H

#include <vector>
#include <memory>
#include <string>
#include <utility>

#include "iBotStrategy.h"

class Game;

class iPlayer {
protected:
    std::vector<bool> *field;

    std::weak_ptr<Game> game;

    std::weak_ptr<iPlayer> nextPlayer;

    std::unique_ptr<iBotStrategy> strategy;

public:
    iPlayer() = default;

    void setGame(std::shared_ptr<Game> game_) noexcept;

    void setField(std::vector<bool> *field_);

    void setNextPlayer(const std::shared_ptr<iPlayer> &nextPlayer) noexcept;

    bool has_moves(const std::vector<bool> *field) const noexcept;

    bool hasGame() const noexcept;

    virtual std::string getName() const = 0;

    void setStrategy(std::unique_ptr<iBotStrategy> strategy) noexcept;

    virtual void nextMove() = 0;

    virtual std::optional<std::vector<bool> > prevMove() = 0;

    virtual std::vector<int> playTurn() = 0;

    virtual ~iPlayer() = default;
};

#endif //ISTATE_H
