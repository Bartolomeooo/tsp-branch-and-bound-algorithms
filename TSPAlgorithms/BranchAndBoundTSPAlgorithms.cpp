#include "BranchAndBoundTSPAlgorithms.h"
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

// Helper function to calculate a more precise lower bound for a state
int BranchAndBoundTSPAlgorithms::calculateBound(CostMatrixGraph& graph, bool visited[], int currentCost) {
    int numOfCities = graph.getNumOfVertexes();
    int bound = currentCost;

    // Add minimal outgoing costs for unvisited cities
    for (int city = 0; city < numOfCities; ++city) {
        if (!visited[city]) {
            int minOutgoing = numeric_limits<int>::max();
            for (int nextCity = 0; nextCity < numOfCities; ++nextCity) {
                if (city != nextCity) {
                    int outgoing = graph.findElement(city, nextCity);
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

// BFS-based Branch and Bound TSP algorithm
int BranchAndBoundTSPAlgorithms::branchAndBoundBFS(CostMatrixGraph& graph, vector<int>& bestPath) {
    int numOfCities = graph.getNumOfVertexes();
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

        updateVisitedFromPath(current.path, visited, numOfCities);

        for (int nextCity = 0; nextCity < numOfCities; ++nextCity) {
            if (!visited[nextCity]) {
                int cost = graph.findElement(current.currentCity, nextCity);
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
int BranchAndBoundTSPAlgorithms::branchAndBoundDFS(CostMatrixGraph& graph, vector<int>& bestPath) {
    int numOfCities = graph.getNumOfVertexes();
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

        updateVisitedFromPath(current.path, visited, numOfCities);

        for (int nextCity = 0; nextCity < numOfCities; ++nextCity) {
            if (!visited[nextCity]) {
                int cost = graph.findElement(current.currentCity, nextCity);
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
int BranchAndBoundTSPAlgorithms::branchAndBoundBestFirst(CostMatrixGraph& graph, vector<int>& bestPath) {
    int numOfCities = graph.getNumOfVertexes();
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

        updateVisitedFromPath(current.path, visited, numOfCities);

        for (int nextCity = 0; nextCity < numOfCities; ++nextCity) {
            if (!visited[nextCity]) {
                int cost = graph.findElement(current.currentCity, nextCity);
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

void BranchAndBoundTSPAlgorithms::updateVisitedFromPath(std::vector<int>& path, bool visited[], int numOfCities) {
    std::fill(visited, visited + numOfCities, false);
    for (int city : path) {
        visited[city] = true;
    }
}