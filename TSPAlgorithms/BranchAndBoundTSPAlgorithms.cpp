#include "BranchAndBoundTSPAlgorithms.h"
#include "PriorityQueue.h"
#include "Stack.h"
#include <vector>
#include <limits>
#include <algorithm>
#include "Queue.h"

using namespace std;

// Helper function to calculate the lower bound for a state
int BranchAndBoundTSPAlgorithms::calculateBound(CostMatrixGraph& graph, vector<int>& path, int currentCost) {
    int numOfCities = graph.getNumOfVertexes();
    int bound = currentCost;

    // Add minimum edge costs for unvisited cities
    for (int city = 0; city < numOfCities; ++city) {
        if (find(path.begin(), path.end(), city) == path.end()) { // City not visited
            int minEdgeCost = numeric_limits<int>::max();
            for (int nextCity = 0; nextCity < numOfCities; ++nextCity) {
                int cost = graph.findElement(city, nextCity);
                if (cost != -1 && city != nextCity) {
                    minEdgeCost = min(minEdgeCost, cost);
                }
            }
            bound += minEdgeCost;
        }
    }

    return bound;
}

// BFS with a priority queue and lower bound consideration
int BranchAndBoundTSPAlgorithms::branchAndBoundBFS(CostMatrixGraph& graph, std::vector<int>& bestPath) {
    int numOfCities = graph.getNumOfVertexes();
    Queue queue;
    std::vector<int> initialPath = {0};  // Start from city 0

    // Calculate bound for the initial state
    int initialBound = calculateBound(graph, initialPath, 0);
    queue.push({initialPath, 0, 0});  // Add the initial state

    int minCost = std::numeric_limits<int>::max();

    while (!queue.empty()) {
        auto current = queue.pop();

        // Skip this state if its bound is greater than or equal to the current minimum cost
        if (current.cost >= minCost) {
            continue;
        }

        if (current.path.size() == numOfCities) {
            // Complete the cycle by returning to the starting city
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

        // Expand the current state
        for (int nextCity = 0; nextCity < numOfCities; ++nextCity) {
            if (std::find(current.path.begin(), current.path.end(), nextCity) == current.path.end()) {
                int cost = graph.findElement(current.currentCity, nextCity);
                if (cost != -1) {
                    std::vector<int> newPath = current.path;
                    newPath.push_back(nextCity);

                    // Calculate new cost and bound
                    int newCost = current.cost + cost;
                    int newBound = calculateBound(graph, newPath, newCost);

                    // Skip this state if its bound is greater than the current minimum cost
                    if (newBound >= minCost) {
                        continue;
                    }

                    queue.push({newPath, newCost, nextCity});
                }
            }
        }
    }

    return minCost;
}

// DFS with lower bound consideration
int BranchAndBoundTSPAlgorithms::branchAndBoundDFS(CostMatrixGraph& graph, vector<int>& bestPath) {
    int numOfCities = graph.getNumOfVertexes();
    Stack stack;
    vector<int> initialPath = {0}; // Start from city 0

    stack.push({initialPath, 0, calculateBound(graph, initialPath, 0), 0});

    int minCost = numeric_limits<int>::max();

    while (!stack.empty()) {
        auto current = stack.pop();

        // Skip this state if its bound is greater than or equal to the current minimum cost
        if (current.bound >= minCost) {
            continue;
        }

        if (current.path.size() == numOfCities) {
            // Complete the cycle by returning to the starting city
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

        // Expand the current state
        for (int nextCity = 0; nextCity < numOfCities; ++nextCity) {
            if (find(current.path.begin(), current.path.end(), nextCity) == current.path.end()) {
                int cost = graph.findElement(current.currentCity, nextCity);
                if (cost != -1) {
                    vector<int> newPath = current.path;
                    newPath.push_back(nextCity);

                    // Calculate new cost and bound
                    int newCost = current.cost + cost;
                    int newBound = calculateBound(graph, newPath, newCost);

                    // Push the new state to the stack
                    stack.push({newPath, newCost, newBound, nextCity});
                }
            }
        }
    }

    return minCost;
}

int BranchAndBoundTSPAlgorithms::branchAndBoundBestFirst(CostMatrixGraph& graph, std::vector<int>& bestPath) {
    int numOfCities = graph.getNumOfVertexes();
    PriorityQueue pq;
    std::vector<int> initialPath = {0}; // Start from city 0

    // Calculate bound for the initial state
    int initialBound = calculateBound(graph, initialPath, 0);
    pq.push({initialPath, 0, initialBound, 0});

    int minCost = std::numeric_limits<int>::max();

    while (!pq.empty()) {
        auto current = pq.pop();

        // Skip this state if its bound is greater than or equal to the current minimum cost
        if (current.bound >= minCost) {
            continue;
        }

        if (current.path.size() == numOfCities) {
            // Complete the cycle by returning to the starting city
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

        // Expand the current state
        for (int nextCity = 0; nextCity < numOfCities; ++nextCity) {
            if (find(current.path.begin(), current.path.end(), nextCity) == current.path.end()) {
                int cost = graph.findElement(current.currentCity, nextCity);
                if (cost != -1) {
                    std::vector<int> newPath = current.path;
                    newPath.push_back(nextCity);

                    // Calculate new cost and bound
                    int newCost = current.cost + cost;
                    int newBound = calculateBound(graph, newPath, newCost);

                    // Push the new state to the priority queue
                    pq.push({newPath, newCost, newBound, nextCity});
                }
            }
        }
    }

    return minCost;
}