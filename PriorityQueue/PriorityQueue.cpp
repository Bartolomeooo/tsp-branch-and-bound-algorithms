#include "PriorityQueue.h"
#include <stdexcept>
#include <algorithm>

PriorityQueue::PriorityQueue()
        : heap(nullptr), capacity(0), size(0) {}

PriorityQueue::~PriorityQueue() {
    delete[] heap;
}

// Adds a new element to the heap and maintains the heap property
void PriorityQueue::push(const Node& node) {
    if (size == capacity) {
        resize(); // Resize the heap if it's full
    }
    heap[size] = node; // Add the new node at the end
    heapifyUp(size); // Restore the heap property
    size++;
}

// Removes and returns the element with the highest priority (smallest bound)
PriorityQueue::Node PriorityQueue::pop() {
    if (empty()) {
        throw std::out_of_range("Priority queue is empty");
    }

    Node topNode = heap[0]; // The root node (highest priority)
    heap[0] = heap[size - 1]; // Move the last node to the root
    size--; // Decrease the size
    if (size > 0) {
        heapifyDown(0); // Restore the heap property
    }
    return topNode;
}

// Checks if the heap is empty
bool PriorityQueue::empty() const {
    return size == 0;
}

// Resizes the dynamic array when capacity is reached
void PriorityQueue::resize() {
    int newCapacity = (capacity == 0) ? 1 : capacity * 2;
    Node* newHeap = new Node[newCapacity];

    for (int i = 0; i < size; i++) {
        newHeap[i] = heap[i];
    }

    delete[] heap;
    heap = newHeap;
    capacity = newCapacity;
}

// Restores the heap property by moving a node up
void PriorityQueue::heapifyUp(int index) {
    while (index > 0) {
        int parentIndex = (index - 1) / 2; // Calculate the parent's index
        if (heap[index] < heap[parentIndex]) {
            std::swap(heap[index], heap[parentIndex]); // Swap with the parent if priority is higher
            index = parentIndex; // Update the current index to the parent's index
        } else {
            break; // Heap property is satisfied
        }
    }
}

// Restores the heap property by moving a node down
void PriorityQueue::heapifyDown(int index) {
    while (true) {
        int leftChild = 2 * index + 1; // Calculate the left child's index
        int rightChild = 2 * index + 2; // Calculate the right child's index
        int smallest = index; // Assume the current node has the highest priority

        if (leftChild < size && heap[leftChild] < heap[smallest]) {
            smallest = leftChild; // Update if the left child has higher priority
        }

        if (rightChild < size && heap[rightChild] < heap[smallest]) {
            smallest = rightChild; // Update if the right child has higher priority
        }

        if (smallest != index) {
            std::swap(heap[index], heap[smallest]); // Swap with the child having higher priority
            index = smallest; // Update the current index
        } else {
            break; // Heap property is satisfied
        }
    }
}
