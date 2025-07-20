//
// Created by pentester on 7/18/25.
//

#ifndef SOLVE_H
#define SOLVE_H

#include <memory>
#include "iBotStrategy.h"
#include "iCheckMove.h"
#include "iState.h"

class iState;

class Game : public std::enable_shared_from_this<Game> {

    int _n, _k;

    std::vector<bool> field;

    std::shared_ptr<iBotStrategy> strategy;
    std::unique_ptr<iCheckMove> checkMove;

    std::shared_ptr<iState> current_turn;


    std::pair<std::shared_ptr<iState>, std::shared_ptr<iState>> players;

public:

    Game(int n, int k, std::shared_ptr<iState> first_player, std::shared_ptr<iState> second_player);

    void Start();

    void print_field() const;

    void setStrategy(std::shared_ptr<iBotStrategy> strategy) noexcept;
    void setMovesChecker(std::unique_ptr<iCheckMove> checkMove) noexcept;

    void prepare() const noexcept;

    void setTurn(std::shared_ptr<iState> turn) noexcept;

    void playTurn() noexcept;
    void nextTurn() noexcept;

    std::shared_ptr<iBotStrategy> getStrategy() const noexcept;

    bool isEnd() const noexcept;


    ~Game() = default;

};

#endif //SOLVE_H
