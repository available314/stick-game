//
// Created by pentester on 7/18/25.
//

#ifndef SOLVE_H
#define SOLVE_H

#include <memory>
#include "iBotStrategy.h"
#include "iCheckMove.h"
#include "iPlayer.h"

class iPlayer;

class Game : public std::enable_shared_from_this<Game> {

    int _n, _a, _b;

    std::vector<bool> field;

    std::shared_ptr<iBotStrategy> strategy;
    std::unique_ptr<iCheckMove> checkMove;

    std::shared_ptr<iPlayer> current_turn;


    std::pair<std::shared_ptr<iPlayer>, std::shared_ptr<iPlayer>> players;

public:

    Game(int n, int k, std::shared_ptr<iPlayer> first_player, std::shared_ptr<iPlayer> second_player);
    Game(int n, int a, int b, std::shared_ptr<iPlayer> first_player, std::shared_ptr<iPlayer> second_player);

    void Start();

    void print_field() const;

    void setStrategy(std::shared_ptr<iBotStrategy> strategy) noexcept;
    void setMovesChecker(std::unique_ptr<iCheckMove> checkMove) noexcept;

    void prepare() const noexcept;

    void setTurn(std::shared_ptr<iPlayer> turn) noexcept;

    void playTurn() noexcept;
    void nextTurn() noexcept;

    std::shared_ptr<iBotStrategy> getStrategy() const noexcept;

    bool isEnd() const noexcept;


    ~Game() = default;

};

#endif //SOLVE_H
