#ifndef QUEUE_H
#define QUEUE_H

#include <vector>
#include <stdexcept>

class Queue {
public:
    // Structure to represent a node in the queue
    struct Node {
        std::vector<int> path;  // The path of the node
        int cost;               // The cost of the node
        int bound;              // The lower bound of the node
        int currentCity;        // The current city in the node
    };

    // Add a new node to the queue
    void push(const Node& node);

    // Remove and return the front node from the queue
    Node pop();

    // Access the front node without removing it
    const Node& front() const;

    // Check if the queue is empty
    bool empty() const;

private:
    std::vector<Node> data;  // Internal storage for the queue
};

#endif // QUEUE_H
