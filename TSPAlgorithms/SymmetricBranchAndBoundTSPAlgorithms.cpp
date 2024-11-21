#include "SymmetricBranchAndBoundTSPAlgorithms.h"
#include "Stack.h"
#include "PriorityQueue.h"
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

// BFS-based Branch and Bound TSP algorithm for symmetric matrices
int SymmetricBranchAndBoundTSPAlgorithms::branchAndBoundBFS(SymmetricCostMatrix& graph, vector<int>& bestPath) {
    int numOfCities = graph.getNumOfCities();
    PriorityQueue pq;  // Use custom PriorityQueue
    vector<int> initialPath = {0};  // Start from city 0
    pq.push({initialPath, 0, 0});
    int minCost = numeric_limits<int>::max();

    while (!pq.empty()) {
        auto current = pq.pop();

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
                    pq.push({newPath, current.cost + cost, nextCity});
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
    stack.push({initialPath, 0, 0});
    int minCost = numeric_limits<int>::max();

    while (!stack.empty()) {
        auto current = stack.pop();

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
                    stack.push({newPath, current.cost + cost, nextCity});
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
    pq.push({initialPath, 0, 0});
    int minCost = numeric_limits<int>::max();

    while (!pq.empty()) {
        auto current = pq.pop();

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
                    pq.push({newPath, current.cost + cost, nextCity});
                }
            }
        }
    }

    return minCost;
}
