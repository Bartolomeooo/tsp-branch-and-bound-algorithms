#include "Queue.h"
#include <stdexcept>
#include <cstring>

// Constructor
Queue::Queue() : data(nullptr), size(0) {}

// Destructor
Queue::~Queue() {
    delete[] data;
}

// Add a new node to the queue
void Queue::push(const Node& node) {
    // Create a new dynamic array with size + 1
    Node* newData = new Node[size + 1];

    // Copy existing elements to the new array
    for (int i = 0; i < size; i++) {
        newData[i] = data[i];
    }

    // Add the new element at the end
    newData[size] = node;

    // Delete the old array and update the pointer
    delete[] data;
    data = newData;

    // Increment the size
    size++;
}

// Remove and return the front node from the queue
Queue::Node Queue::pop() {
    if (empty()) {
        throw std::out_of_range("Queue is empty");
    }

    // Store the front element
    Node frontNode = data[0];

    // Create a new dynamic array with size - 1
    Node* newData = new Node[size - 1];

    // Copy all elements except the first to the new array
    for (int i = 1; i < size; i++) {
        newData[i - 1] = data[i];
    }

    // Delete the old array and update the pointer
    delete[] data;
    data = newData;

    // Decrement the size
    size--;

    return frontNode;
}

// Access the front node without removing it
const Queue::Node& Queue::front() const {
    if (empty()) {
        throw std::out_of_range("Queue is empty");
    }
    return data[0];
}

// Check if the queue is empty
bool Queue::empty() const {
    return size == 0;
}
