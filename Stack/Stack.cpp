// Stack.cpp
#include "Stack.h"
#include <stdexcept>

void Stack::push(const Node& state) {
    stack.push_back(state);
}

Stack::Node Stack::pop() {
    if (stack.empty()) {
        throw std::out_of_range("Stack is empty");
    }

    Node node = stack.back();
    stack.pop_back();
    return node;
}

bool Stack::empty() const {
    return stack.empty();
}
