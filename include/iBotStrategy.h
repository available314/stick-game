//
// Created by pentester on 7/18/25.
//

#ifndef ISTRATEGY_H
#define ISTRATEGY_H
#include <optional>
#include <vector>

class iBotStrategy {
public:
    iBotStrategy() noexcept = default;

    virtual void build() = 0;

    virtual std::optional<std::vector<int> > go_win(const std::vector<bool> *state) noexcept = 0;

    virtual std::optional<std::vector<int> > rand_walk(const std::vector<bool> *state) noexcept = 0;

    std::vector<int> do_turn(const std::vector<bool> *state);

    std::vector<std::pair<int, int> > get_state_by_field(const std::vector<bool> *state) noexcept;

    virtual bool is_over(const std::vector<bool> *field) noexcept = 0;

    virtual ~iBotStrategy() = default;
};


#endif //ISTRATEGY_H
