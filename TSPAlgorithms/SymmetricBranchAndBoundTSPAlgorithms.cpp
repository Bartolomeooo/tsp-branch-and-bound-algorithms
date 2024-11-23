#include "SymmetricBranchAndBoundTSPAlgorithms.h"
#include "Stack.h"
#include "PriorityQueue.h"
#include <vector>
#include <limits>
#include <algorithm>

#include "Queue.h"

using namespace std;

// Helper function to calculate the lower bound for a state
int calculateBound(const SymmetricCostMatrix& graph, const vector<int>& path, int currentCost) {
    int numOfCities = graph.getNumOfCities();
    int bound = currentCost;

    // Include the minimum edge cost for unvisited cities
    for (int city = 0; city < numOfCities; ++city) {
        if (find(path.begin(), path.end(), city) == path.end()) { // City not visited
            int minEdgeCost = numeric_limits<int>::max();
            for (int nextCity = 0; nextCity < numOfCities; ++nextCity) {
                if (city != nextCity && find(path.begin(), path.end(), nextCity) == path.end()) {
                    int cost = graph.getCost(city, nextCity);
                    if (cost != -1) {
                        minEdgeCost = min(minEdgeCost, cost);
                    }
                }
            }
            bound += minEdgeCost;
        }
    }

    return bound;
}

// BFS-based Branch and Bound TSP algorithm for symmetric matrices
int SymmetricBranchAndBoundTSPAlgorithms::branchAndBoundBFS(SymmetricCostMatrix& graph, vector<int>& bestPath) {
    int numOfCities = graph.getNumOfCities();
    Queue queue;  // Use custom PriorityQueue
    vector<int> initialPath = {0};  // Start from city 0
    int initialBound = calculateBound(graph, initialPath, 0);
    queue.push({initialPath, 0, 0});
    int minCost = numeric_limits<int>::max();

    while (!queue.empty()) {
        auto current = queue.pop();

        if (current.cost >= minCost) {
            continue; // Skip branches that exceed the current minimum cost
        }

        if (current.path.size() == numOfCities) {
            // Complete the cycle by returning to the start
            int costToStart = graph.getCost(current.currentCity, 0);
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

        // Expand the current state
        for (int nextCity = 0; nextCity < numOfCities; ++nextCity) {
            if (find(current.path.begin(), current.path.end(), nextCity) == current.path.end()) {
                int cost = graph.getCost(current.currentCity, nextCity);
                if (cost != -1) {
                    vector<int> newPath = current.path;
                    newPath.push_back(nextCity);

                    int newCost = current.cost + cost;
                    int newBound = calculateBound(graph, newPath, newCost);
                    queue.push({newPath, newCost, nextCity});
                }
            }
        }
    }

    return minCost;
}

// DFS-based Branch and Bound TSP algorithm for symmetric matrices
int SymmetricBranchAndBoundTSPAlgorithms::branchAndBoundDFS(SymmetricCostMatrix& graph, vector<int>& bestPath) {
    int numOfCities = graph.getNumOfCities();
    Stack stack;  // Use custom Stack
    vector<int> initialPath = {0};  // Start from city 0
    int initialBound = calculateBound(graph, initialPath, 0);
    stack.push({initialPath, 0, initialBound, 0});
    int minCost = numeric_limits<int>::max();

    while (!stack.empty()) {
        auto current = stack.pop();

        if (current.bound >= minCost) {
            continue; // Skip branches that exceed the current minimum cost
        }

        if (current.path.size() == numOfCities) {
            // Complete the cycle by returning to the start
            int costToStart = graph.getCost(current.currentCity, 0);
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

        // Expand the current state
        for (int nextCity = numOfCities - 1; nextCity >= 0; --nextCity) {
            if (find(current.path.begin(), current.path.end(), nextCity) == current.path.end()) {
                int cost = graph.getCost(current.currentCity, nextCity);
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

// Best-First Search-based Branch and Bound TSP algorithm for symmetric matrices
int SymmetricBranchAndBoundTSPAlgorithms::branchAndBoundBestFirst(SymmetricCostMatrix& graph, vector<int>& bestPath) {
    int numOfCities = graph.getNumOfCities();
    PriorityQueue pq;  // Use custom PriorityQueue
    vector<int> initialPath = {0};  // Start from city 0
    int initialBound = calculateBound(graph, initialPath, 0);
    pq.push({initialPath, 0, initialBound, 0});
    int minCost = numeric_limits<int>::max();

    while (!pq.empty()) {
        auto current = pq.pop();

        if (current.bound >= minCost) {
            continue; // Skip branches that exceed the current minimum cost
        }

        if (current.path.size() == numOfCities) {
            // Complete the cycle by returning to the start
            int costToStart = graph.getCost(current.currentCity, 0);
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

        // Expand the current state with heuristic prioritization
        for (int nextCity = 0; nextCity < numOfCities; ++nextCity) {
            if (find(current.path.begin(), current.path.end(), nextCity) == current.path.end()) {
                int cost = graph.getCost(current.currentCity, nextCity);
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
