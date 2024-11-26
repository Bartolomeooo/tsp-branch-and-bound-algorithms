#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <vector>

class PriorityQueue {
public:
    struct Node {
        std::vector<int> path;
        int cost;
        int bound;
        int currentCity;

        // Comparison operator for heap logic
        bool operator<(const Node& other) const {
            return bound < other.bound; // Lower bound means higher priority
        }
    };

    PriorityQueue(); // Constructor
    ~PriorityQueue(); // Destructor

    void push(const Node& node);
    Node pop();
    bool empty() const;

private:
    // Internal heap storage
    Node* heap; // Dynamic array
    int capacity; // Current capacity of the array
    int size; // Current number of elements in the heap

    // Heap management functions
    void heapifyUp(int index);
    void heapifyDown(int index);
    void resize(); // Resize the array when full
};

#endif // PRIORITY_QUEUE_H
