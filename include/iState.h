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

    std::shared_ptr<Game> game;

public:
    iState() = default;

    void setField(const std::vector<bool> &field);

    virtual void nextMove() = 0;
    virtual void prevMove() = 0;

    virtual ~iState() = default;
};

#endif //ISTATE_H
