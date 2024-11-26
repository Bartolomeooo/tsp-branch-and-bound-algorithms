#include "Stack.h"

// Constructor
Stack::Stack() : stack(nullptr), size(0) {}

// Destructor
Stack::~Stack() {
    delete[] stack;
}

// Push a node onto the stack
void Stack::push(const Node& node) {
    // Create a new dynamic array with size + 1
    Node* newStack = new Node[size + 1];

    // Copy existing elements to the new array
    for (int i = 0; i < size; i++) {
        newStack[i] = stack[i];
    }

    // Add the new element at the end
    newStack[size] = node;

    // Delete the old array and update the pointer
    delete[] stack;
    stack = newStack;

    // Increment the size
    size++;
}

// Pop a node from the stack
Stack::Node Stack::pop() {
    if (empty()) {
        throw std::out_of_range("Stack is empty");
    }

    // Store the top element
    Node topNode = stack[size - 1];

    // Create a new dynamic array with size - 1
    Node* newStack = new Node[size - 1];

    // Copy all elements except the last one to the new array
    for (int i = 0; i < size - 1; i++) {
        newStack[i] = stack[i];
    }

    // Delete the old array and update the pointer
    delete[] stack;
    stack = newStack;

    // Decrement the size
    size--;

    return topNode;
}

// Check if the stack is empty
bool Stack::empty() const {
    return size == 0;
}
