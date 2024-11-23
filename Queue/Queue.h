#ifndef QUEUE_H
#define QUEUE_H

#include <vector>
#include <stdexcept>

class Queue {
public:
    // Structure to represent a state in the queue
    struct State {
        std::vector<int> path;  // The path of the state
        int cost;               // The cost of the state
        int currentCity;        // The current city in the state
    };

    // Add a new state to the queue
    void push(const State& state);

    // Remove and return the front state from the queue
    State pop();

    // Access the front state without removing it
    const State& front() const;

    // Check if the queue is empty
    bool empty() const;

private:
    std::vector<State> data;  // Internal storage for the queue
};

#endif // QUEUE_H
