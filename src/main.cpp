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

#include "NormalModeStrategy.h"


int main() {
    int n = 50;


    auto start = std::chrono::steady_clock::now();

    auto solve = std::make_shared<Game>(n, 0, 0, std::make_shared<Bot>(std::string{"grundy_bot"}),
                                        std::make_shared<Human>(std::string{"graph_bot"}));

    solve->setStrategyForFirstPlayer(std::make_unique<NormalModeStrategy>(n));
    solve->setMovesChecker(std::make_unique<RowMove>());

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";

    solve->Start();

    while (!solve->isEnd()) {
        solve->playTurn();
        solve->nextTurn();
    }

    solve->print_field();
    std::cout << "loser: " << solve->loser();

    return 0;
}
