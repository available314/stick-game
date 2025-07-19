#include <chrono>
#include <iostream>
#include <memory>

#include "Game.h"
#include "human.h"
#include "RowMove.h"
#include "RowStrategy.h"

int main() {

    int n, k;
    std::cin >> n >> k;


    auto start = std::chrono::steady_clock::now();

    auto solve = std::make_shared<Game>(std::make_shared<Human>(std::string{"first"}), std::make_shared<Human>(std::string{"second"}));
    solve->setStrategy(std::make_unique<RowStrategy>(n, k));
    solve->setMovesChecker(std::make_unique<RowMove>());
    solve->prepare();

    // solve.create_move(vector<int> pos -> sticks we delete)
    // need to create a strategy class for checking correctness of move

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;
}