//
// Created by pentester on 7/18/25.
//

#ifndef ISTRATEGY_H
#define ISTRATEGY_H
#include <optional>
#include <vector>

class iBotStrategy {
public:

    iBotStrategy() = default;

    virtual void build() = 0;
    virtual std::optional<std::vector<std::pair<int, int>>> get_next_win_state(const std::vector<std::pair<int, int>> &cur_state) noexcept = 0;

    virtual std::optional<std::vector<int>> make_transition(const std::vector<bool> &from, const std::vector<std::pair<int, int>> &to) noexcept = 0;

    virtual bool is_over(const std::vector<bool> *field) noexcept = 0;

    virtual ~iBotStrategy() = default;
};


#endif //ISTRATEGY_H
