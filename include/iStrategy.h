//
// Created by pentester on 7/18/25.
//

#ifndef ISTRATEGY_H
#define ISTRATEGY_H

class iStrategy {
public:

    iStrategy() = default;

    virtual void build() = 0;

    virtual ~iStrategy() = default;
};


#endif //ISTRATEGY_H
