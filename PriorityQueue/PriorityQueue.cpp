#include "PriorityQueue.h"

#include <stdexcept>

void PriorityQueue::push(const Node& state) {
    queue.push_back(state);
    int index = queue.size() - 1;
    while (index > 0 && queue[index].bound < queue[index - 1].bound) {
        std::swap(queue[index], queue[index - 1]);
        --index;
    }
}
PriorityQueue::Node PriorityQueue::pop() {
    if (queue.empty()) {
        throw std::out_of_range("Priority queue is empty");
    }

    // Retrieve the state with the lowest cost.
    Node state = queue.front();

    // Remove the state from the queue.
    queue.erase(queue.begin());

    return state;
}

bool PriorityQueue::empty() const {
    return queue.empty();
}
