//
// Created by pentester on 7/19/25.
//

#ifndef ISTATE_H
#define ISTATE_H

#include <vector>
#include <memory>
#include <string>
#include <utility>

class Game;

class iState {
protected:

    std::vector<bool> *field;

    std::weak_ptr<Game> game;

    std::weak_ptr<iState> nextPlayer;

public:
    iState() = default;

    void setGame(std::shared_ptr<Game> game_) noexcept;
    void setField(std::vector<bool> *field_);
    void setNextPlayer(const std::shared_ptr<iState> &nextPlayer) noexcept;

    static std::vector<std::pair<int, int>> get_state_by_field(const std::vector<bool> *state) noexcept;

    virtual std::string getName() const = 0;
    virtual void nextMove() = 0;
    virtual void prevMove() = 0;
    virtual std::vector<int> playTurn() = 0;

    virtual ~iState() = default;
};

#endif //ISTATE_H
