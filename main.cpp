#include <iostream>
#include <memory>


class iStrategy {
public:

    iStrategy() = default;

    virtual void build(int n, int k) = delete;

    virtual ~iStrategy() = default;
};


class RowStrategy final : public iStrategy {
public:

    RowStrategy() = default;

    void build(int n, int k) override {

    }

    ~RowStrategy() override = default;
};

class Solve {

    std::unique_ptr<iStrategy> strategy;



public:

    Solve() = default;

    void setStrategy(std::unique_ptr<iStrategy> strategy) {
        this->strategy = std::move(strategy);
    }

    void prepare();


    ~Solve() = default;

};

int main() {

    Solve solve;

    solve.setStrategy(std::make_unique<RowStrategy>());


    solve.prepare();

    return 0;
}