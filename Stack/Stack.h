#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

class Stack {
public:
    struct Node {
        std::vector<int> path;  // Path of the node
        int cost;               // Cost of the node
        int bound;              // Bound of the node
        int currentCity;        // Current city in the node
    };

    Stack();  // Constructor
    ~Stack(); // Destructor

    // Push a node onto the stack
    void push(const Node& node);

    // Pop a node from the stack
    Node pop();

    // Check if the stack is empty
    bool empty() const;

private:
    Node* stack;     // Dynamic array for storing nodes
    int size;        // Current number of elements in the stack
};

#endif // STACK_H
