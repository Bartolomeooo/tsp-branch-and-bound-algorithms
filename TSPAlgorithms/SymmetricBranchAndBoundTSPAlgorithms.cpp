#include "SymmetricBranchAndBoundTSPAlgorithms.h"
#include "Queue.h"
#include "Stack.h"
#include "PriorityQueue.h"
#include <algorithm>
#include <limits>

using namespace std;

// Calculate a precise lower bound for a state
int SymmetricBranchAndBoundTSPAlgorithms::calculateBound(SymmetricCostMatrix& graph, bool visited[], int currentCost) {
    int numOfCities = graph.getNumOfCities();
    int bound = currentCost;

    // Add minimal outgoing costs for unvisited cities
    for (int city = 0; city < numOfCities; ++city) {
        if (!visited[city]) {
            int minOutgoing = numeric_limits<int>::max();
            for (int nextCity = 0; nextCity < numOfCities; ++nextCity) {
                if (city != nextCity) {
                    int outgoing = graph.getCost(city, nextCity);
                    if (outgoing != -1) {
                        minOutgoing = min(minOutgoing, outgoing);
                    }
                }
            }
            bound += minOutgoing;
        }
    }

    return bound;
}

void SymmetricBranchAndBoundTSPAlgorithms::updateVisitedFromPath(std::vector<int>& path, bool visited[], int numOfCities) {
    std::fill(visited, visited + numOfCities, false);
    for (int city : path) {
        visited[city] = true;
    }
}

// BFS-based Branch and Bound TSP algorithm
int SymmetricBranchAndBoundTSPAlgorithms::branchAndBoundBFS(SymmetricCostMatrix& graph, vector<int>& bestPath) {
    int numOfCities = graph.getNumOfCities();
    Queue queue;  // FIFO queue
    vector<int> initialPath = {0};  // Start from city 0

    bool visited[numOfCities];
    updateVisitedFromPath(initialPath, visited, numOfCities);

    queue.push({initialPath, 0, calculateBound(graph, visited, 0), 0});
    int minCost = numeric_limits<int>::max();

    while (!queue.empty()) {
        auto current = queue.pop();

        if (current.bound >= minCost) {
            continue;
        }

        if (current.path.size() == numOfCities) {
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

        updateVisitedFromPath(current.path, visited, numOfCities);

        for (int nextCity = 0; nextCity < numOfCities; ++nextCity) {
            if (!visited[nextCity]) {
                int cost = graph.getCost(current.currentCity, nextCity);
                if (cost != -1) {
                    vector<int> newPath = current.path;
                    newPath.push_back(nextCity);
                    int newCost = current.cost + cost;
                    updateVisitedFromPath(newPath, visited, numOfCities);
                    int newBound = calculateBound(graph, visited, newCost);

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
int SymmetricBranchAndBoundTSPAlgorithms::branchAndBoundDFS(SymmetricCostMatrix& graph, vector<int>& bestPath) {
    int numOfCities = graph.getNumOfCities();
    Stack stack;
    vector<int> initialPath = {0}; // Start from city 0

    bool visited[numOfCities];
    updateVisitedFromPath(initialPath, visited, numOfCities);

    stack.push({initialPath, 0, calculateBound(graph, visited, 0), 0});
    int minCost = numeric_limits<int>::max();

    while (!stack.empty()) {
        auto current = stack.pop();

        if (current.bound >= minCost) {
            continue;
        }

        if (current.path.size() == numOfCities) {
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

        updateVisitedFromPath(current.path, visited, numOfCities);

        for (int nextCity = 0; nextCity < numOfCities; ++nextCity) {
            if (!visited[nextCity]) {
                int cost = graph.getCost(current.currentCity, nextCity);
                if (cost != -1) {
                    vector<int> newPath = current.path;
                    newPath.push_back(nextCity);
                    int newCost = current.cost + cost;
                    updateVisitedFromPath(newPath, visited, numOfCities);
                    int newBound = calculateBound(graph, visited, newCost);

                    if (newBound < minCost) {
                        stack.push({newPath, newCost, newBound, nextCity});
                    }
                }
            }
        }
    }

    return minCost;
}

// Best-First Search-based Branch and Bound TSP algorithm
int SymmetricBranchAndBoundTSPAlgorithms::branchAndBoundBestFirst(SymmetricCostMatrix& graph, vector<int>& bestPath) {
    int numOfCities = graph.getNumOfCities();
    PriorityQueue pq;
    vector<int> initialPath = {0}; // Start from city 0

    bool visited[numOfCities];
    updateVisitedFromPath(initialPath, visited, numOfCities);

    pq.push({initialPath, 0, calculateBound(graph, visited, 0), 0});
    int minCost = numeric_limits<int>::max();

    while (!pq.empty()) {
        auto current = pq.pop();

        if (current.bound >= minCost) {
            continue;
        }

        if (current.path.size() == numOfCities) {
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

        updateVisitedFromPath(current.path, visited, numOfCities);

        for (int nextCity = 0; nextCity < numOfCities; ++nextCity) {
            if (!visited[nextCity]) {
                int cost = graph.getCost(current.currentCity, nextCity);
                if (cost != -1) {
                    vector<int> newPath = current.path;
                    newPath.push_back(nextCity);
                    int newCost = current.cost + cost;
                    updateVisitedFromPath(newPath, visited, numOfCities);
                    int newBound = calculateBound(graph, visited, newCost);

                    if (newBound < minCost) {
                        pq.push({newPath, newCost, newBound, nextCity});
                    }
                }
            }
        }
    }

    return minCost;
}
