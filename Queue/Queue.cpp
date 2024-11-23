#include "Queue.h"

// Add a new state to the queue
void Queue::push(const State& state) {
    data.push_back(state);
}

// Remove and return the front state from the queue
Queue::State Queue::pop() {
    if (empty()) {
        throw std::out_of_range("Queue is empty");
    }
    State frontState = data.front();
    data.erase(data.begin());
    return frontState;
}

// Access the front state without removing it
const Queue::State& Queue::front() const {
    if (empty()) {
        throw std::out_of_range("Queue is empty");
    }
    return data.front();
}

// Check if the queue is empty
bool Queue::empty() const {
    return data.empty();
}
