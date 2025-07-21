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

int main() {
    int n, k;
    std::cin >> n >> k;


    //auto start = std::chrono::steady_clock::now();

    auto solve = std::make_shared<Game>(n, k, std::make_shared<Bot>(std::string{"egor"}),
                                        std::make_shared<Bot>(std::string{"grundy_bot"}));
    solve->setStrategy(std::make_shared<RowGrundyStrategy>(n, k));
    solve->setMovesChecker(std::make_unique<RowMove>());
    solve->prepare();

    //auto end = std::chrono::steady_clock::now();
    //std::chrono::duration<double> elapsed_seconds = end - start;
    //std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";

    solve->Start();

    while (!solve->isEnd()) {
        solve->playTurn();
        solve->nextTurn();
    }

    std::cout << "loser: " << solve->loser();

    return 0;
}
