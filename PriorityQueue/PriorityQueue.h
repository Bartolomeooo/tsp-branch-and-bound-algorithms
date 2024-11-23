// PriorityQueue.h
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <vector>
#include <AlgorithmUtils.h>

class PriorityQueue {
public:
    struct State {
        std::vector<int> path;
        int cost;
        int bound;
        int currentCity;
    };

    void push(const State& state);
    State pop();
    bool empty() const;

private:
    std::vector<State> queue;
};

#endif // PRIORITY_QUEUE_H
