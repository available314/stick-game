#include <chrono>
#include <iostream>
#include <memory>

#include "bot.h"
#include "Game.h"
#include "human.h"
#include "RowMove.h"
#include "RowGraphStrategy.h"
#include "RowGrundyStrategy.h"
#include "StandardMove.h"
#include "StandardStrategy.h"

#include <SFML/Graphics.hpp>


int main() {
    int n, a, b;
    std::cin >> n >> a >> b;


    //auto start = std::chrono::steady_clock::now();

    auto solve = std::make_shared<Game>(n, a, b, std::make_shared<Bot>(std::string{"grundy_bot"}),
                                        std::make_shared<Bot>(std::string{"graph_bot"}));

    solve->setStrategyForFirstPlayer(std::make_unique<RowGrundyStrategy>(n, a, b));
    solve->setStrategyForSecondPlayer(std::make_unique<RowGraphStrategy>(n, a, b));
    solve->setMovesChecker(std::make_unique<RowMove>());

    //auto end = std::chrono::steady_clock::now();
    //std::chrono::duration<double> elapsed_seconds = end - start;
    //std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";

    solve->Start();

    while (!solve->isEnd()) {
        solve->playTurn();
        solve->nextTurn();
    }

    solve->print_field();
    std::cout << "loser: " << solve->loser();

    return 0;
}
