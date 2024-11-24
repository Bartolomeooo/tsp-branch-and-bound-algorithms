// PriorityQueue.h
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <vector>
#include <AlgorithmUtils.h>

class PriorityQueue {
public:
    struct Node {
        std::vector<int> path;
        int cost;
        int bound;
        int currentCity;
    };

    void push(const Node& node);
    Node pop();
    bool empty() const;

private:
    std::vector<Node> queue;
};

#endif // PRIORITY_QUEUE_H
