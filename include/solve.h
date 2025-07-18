//
// Created by pentester on 7/18/25.
//

#ifndef SOLVE_H
#define SOLVE_H

#include <memory>
#include "iStrategy.h"

class Solve {

    std::unique_ptr<iStrategy> strategy;

public:

    Solve() = default;

    void setStrategy(std::unique_ptr<iStrategy> strategy) noexcept;

    void prepare() noexcept;


    ~Solve() = default;

};

#endif //SOLVE_H
