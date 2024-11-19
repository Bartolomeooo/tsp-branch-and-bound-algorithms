#include "PriorityQueue.h"

#include <stdexcept>

void PriorityQueue::push(const State& state) {
    // Add the new state to the vector.
    queue.push_back(state);

    // Reorganize the vector to maintain the priority property (lowest cost first).
    int index = queue.size() - 1;
    while (index > 0 && queue[index].cost < queue[index - 1].cost) {
        std::swap(queue[index], queue[index - 1]);
        --index;
    }
}

PriorityQueue::State PriorityQueue::pop() {
    if (queue.empty()) {
        throw std::out_of_range("Priority queue is empty");
    }

    // Retrieve the state with the lowest cost.
    State state = queue.front();

    // Remove the state from the queue.
    queue.erase(queue.begin());

    return state;
}

bool PriorityQueue::empty() const {
    return queue.empty();
}
