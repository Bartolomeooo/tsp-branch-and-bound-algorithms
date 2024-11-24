#include "BranchAndBoundTSPAlgorithms.h"
#include <unordered_set>
#include <algorithm>

using namespace std;

// Helper function to calculate a more precise lower bound for a state
int BranchAndBoundTSPAlgorithms::calculateBound(CostMatrixGraph& graph, vector<int>& path, int currentCost) {
    int numOfCities = graph.getNumOfVertexes();
    int bound = currentCost;

    unordered_set<int> visited(path.begin(), path.end());

    // Add minimal outgoing and incoming costs for unvisited cities
    for (int city = 0; city < numOfCities; ++city) {
        if (visited.find(city) == visited.end()) {
            int minOutgoing = numeric_limits<int>::max();
            for (int nextCity = 0; nextCity < numOfCities; ++nextCity) {
                if (city != nextCity) {
                    int outgoing = graph.findElement(city, nextCity);
                    if (outgoing != -1) {
                        minOutgoing = min( minOutgoing, outgoing);
                    }
                }
            }
            bound += minOutgoing;
        }
    }

    return bound;
}


// BFS-based Branch and Bound TSP algorithm
int BranchAndBoundTSPAlgorithms::branchAndBoundBFS(CostMatrixGraph& graph, vector<int>& bestPath) {
    int numOfCities = graph.getNumOfVertexes();
    Queue queue;  // FIFO queue
    vector<int> initialPath = {0};  // Start from city 0

    queue.push({initialPath, 0, calculateBound(graph, initialPath, 0), 0});
    int minCost = numeric_limits<int>::max();

    while (!queue.empty()) {
        auto current = queue.pop();

        // Skip states with bound exceeding current minimum cost
        if (current.bound >= minCost) {
            continue;
        }

        if (current.path.size() == numOfCities) {
            // Complete the cycle by returning to the start
            int costToStart = graph.findElement(current.currentCity, 0);
            if (costToStart != -1) {
                int totalCost = current.cost + costToStart;
                if (totalCost < minCost) {
                    minCost = totalCost;
                    bestPath = current.path;
                    bestPath.push_back(0);
                }
            }
            continue;
        }

        unordered_set<int> visited(current.path.begin(), current.path.end());
        for (int nextCity = 0; nextCity < numOfCities; ++nextCity) {
            if (visited.find(nextCity) == visited.end()) {
                int cost = graph.findElement(current.currentCity, nextCity);
                if (cost != -1) {
                    vector<int> newPath = current.path;
                    newPath.push_back(nextCity);
                    int newCost = current.cost + cost;
                    int newBound = calculateBound(graph, newPath, newCost);

                    if (newBound < minCost) {
                        queue.push({newPath, newCost, newBound, nextCity});
                    }
                }
            }
        }
    }

    return minCost;
}

// DFS-based Branch and Bound TSP algorithm
int BranchAndBoundTSPAlgorithms::branchAndBoundDFS(CostMatrixGraph& graph, vector<int>& bestPath) {
    int numOfCities = graph.getNumOfVertexes();
    Stack stack;
    vector<int> initialPath = {0}; // Start from city 0

    stack.push({initialPath, 0, calculateBound(graph, initialPath, 0), 0});
    int minCost = numeric_limits<int>::max();

    while (!stack.empty()) {
        auto current = stack.pop();

        if (current.bound >= minCost) {
            continue;
        }

        if (current.path.size() == numOfCities) {
            int costToStart = graph.findElement(current.currentCity, 0);
            if (costToStart != -1) {
                int totalCost = current.cost + costToStart;
                if (totalCost < minCost) {
                    minCost = totalCost;
                    bestPath = current.path;
                    bestPath.push_back(0);
                }
            }
            continue;
        }

        unordered_set<int> visited(current.path.begin(), current.path.end());
        for (int nextCity = 0; nextCity < numOfCities; ++nextCity) {
            if (visited.find(nextCity) == visited.end()) {
                int cost = graph.findElement(current.currentCity, nextCity);
                if (cost != -1) {
                    vector<int> newPath = current.path;
                    newPath.push_back(nextCity);
                    int newCost = current.cost + cost;
                    int newBound = calculateBound(graph, newPath, newCost);

                    stack.push({newPath, newCost, newBound, nextCity});
                }
            }
        }
    }

    return minCost;
}

// Best-First Search-based Branch and Bound TSP algorithm
int BranchAndBoundTSPAlgorithms::branchAndBoundBestFirst(CostMatrixGraph& graph, vector<int>& bestPath) {
    int numOfCities = graph.getNumOfVertexes();
    PriorityQueue pq;
    vector<int> initialPath = {0}; // Start from city 0

    pq.push({initialPath, 0, calculateBound(graph, initialPath, 0), 0});
    int minCost = numeric_limits<int>::max();

    while (!pq.empty()) {
        auto current = pq.pop();

        if (current.bound >= minCost) {
            continue;
        }

        if (current.path.size() == numOfCities) {
            int costToStart = graph.findElement(current.currentCity, 0);
            if (costToStart != -1) {
                int totalCost = current.cost + costToStart;
                if (totalCost < minCost) {
                    minCost = totalCost;
                    bestPath = current.path;
                    bestPath.push_back(0);
                }
            }
            continue;
        }

        unordered_set<int> visited(current.path.begin(), current.path.end());
        for (int nextCity = 0; nextCity < numOfCities; ++nextCity) {
            if (visited.find(nextCity) == visited.end()) {
                int cost = graph.findElement(current.currentCity, nextCity);
                if (cost != -1) {
                    vector<int> newPath = current.path;
                    newPath.push_back(nextCity);
                    int newCost = current.cost + cost;
                    int newBound = calculateBound(graph, newPath, newCost);

                    pq.push({newPath, newCost, newBound, nextCity});
                }
            }
        }
    }

    return minCost;
}
