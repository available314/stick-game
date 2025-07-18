#include <chrono>
#include <iostream>
#include <memory>

#include "solve.h"
#include "RowStrategy.h"

int main() {

    int n, k;
    std::cin >> n >> k;


    auto start = std::chrono::steady_clock::now();

    Solve solve;
    solve.setStrategy(std::make_unique<RowStrategy>(n, k));
    solve.prepare();

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;
}