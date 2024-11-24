#include "Queue.h"

// Add a new state to the queue
void Queue::push(const Node& node) {
    data.push_back(node);
}

// Remove and return the front state from the queue
Queue::Node Queue::pop() {
    if (empty()) {
        throw std::out_of_range("Queue is empty");
    }
    Node frontNode = data.front();
    data.erase(data.begin());
    return frontNode;
}

// Access the front state without removing it
const Queue::Node& Queue::front() const {
    if (empty()) {
        throw std::out_of_range("Queue is empty");
    }
    return data.front();
}

// Check if the queue is empty
bool Queue::empty() const {
    return data.empty();
}
