//
// Created by pentester on 7/18/25.
//

#ifndef ISTRATEGY_H
#define ISTRATEGY_H

class iBotStrategy {
public:

    iBotStrategy() = default;

    virtual void build() = 0;

    virtual ~iBotStrategy() = default;
};


#endif //ISTRATEGY_H
