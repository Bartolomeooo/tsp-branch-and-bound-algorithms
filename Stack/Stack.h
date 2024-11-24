// Stack.h
#ifndef STACK_H
#define STACK_H

#include <vector>

class Stack {
public:
    struct Node {
        std::vector<int> path;
        int cost;
        int bound;
        int currentCity;
    };

    // Push a node onto the stack
    void push(const Node& node);

    // Pop a node from the stack
    Node pop();

    // Check if the stack is empty
    bool empty() const;

private:
    std::vector<Node> stack;
};

#endif // STACK_H
