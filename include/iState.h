//
// Created by pentester on 7/19/25.
//

#ifndef ISTATE_H
#define ISTATE_H

#include <vector>
#include <memory>

class Game;

class iState {
protected:

    std::vector<bool> field;

    std::weak_ptr<Game> game;

    std::weak_ptr<iState> nextPlayer;

public:
    iState() = default;

    void setGame(std::shared_ptr<Game> game_) noexcept;
    void setField(const std::vector<bool> &field);
    void setNextPlayer(std::shared_ptr<iState> nextPlayer) noexcept;

    virtual void nextMove() = 0;
    virtual void prevMove() = 0;

    virtual ~iState() = default;
};

#endif //ISTATE_H
