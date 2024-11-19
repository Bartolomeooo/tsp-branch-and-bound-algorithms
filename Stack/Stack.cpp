// Stack.cpp
#include "Stack.h"
#include <stdexcept>

void Stack::push(const State& state) {
    stack.push_back(state);
}

Stack::State Stack::pop() {
    if (stack.empty()) {
        throw std::out_of_range("Stack is empty");
    }

    State state = stack.back();
    stack.pop_back();
    return state;
}

bool Stack::empty() const {
    return stack.empty();
}
