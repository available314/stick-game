//
// Created by pentester on 7/18/25.
//

#include "solve.h"

void Solve::setStrategy(std::unique_ptr<iStrategy> strategy) noexcept {
    this->strategy = std::move(strategy);
}


void Solve::prepare() noexcept {
    strategy->build();
}