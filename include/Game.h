//
// Created by pentester on 7/18/25.
//

#ifndef SOLVE_H
#define SOLVE_H

#include <memory>
#include "iBotStrategy.h"
#include "iCheckMove.h"

class Game {

    std::unique_ptr<iBotStrategy> strategy;
    std::unique_ptr<iCheckMove> checkMove;
    std::vector<bool> field;

public:

    Game() = default;

    void setStrategy(std::unique_ptr<iBotStrategy> strategy) noexcept;
    void setMovesChecker(std::unique_ptr<iCheckMove> checkMove) noexcept;

    void prepare() noexcept;


    ~Game() = default;

};

#endif //SOLVE_H
