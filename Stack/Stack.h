// Stack.h
#ifndef STACK_H
#define STACK_H

#include <vector>

class Stack {
public:
    struct State {
        std::vector<int> path;
        int cost;
        int bound;
        int currentCity;
    };

    // Push a state onto the stack
    void push(const State& state);

    // Pop a state from the stack
    State pop();

    // Check if the stack is empty
    bool empty() const;

private:
    std::vector<State> stack;
};

#endif // STACK_H
