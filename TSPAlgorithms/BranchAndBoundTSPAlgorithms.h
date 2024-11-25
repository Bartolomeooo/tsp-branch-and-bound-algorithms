#ifndef TRAVELLING_SALESMAN_PROBLEM_BRANCHANDBOUNDTSPALGORITHMS_H
#define TRAVELLING_SALESMAN_PROBLEM_BRANCHANDBOUNDTSPALGORITHMS_H

#include "CostMatrixGraph.h"
#include <vector>
#include <Queue.h>
#include <PriorityQueue.h>
#include <Stack.h>

class BranchAndBoundTSPAlgorithms {
public:
    // BFS-based Branch and Bound TSP algorithm
    static int branchAndBoundBFS(CostMatrixGraph& graph, std::vector<int>& bestPath);

    // DFS-based Branch and Bound TSP algorithm
    static int branchAndBoundDFS(CostMatrixGraph& graph, std::vector<int>& bestPath);

    // Best-First Search-based Branch and Bound TSP algorithm
    static int branchAndBoundBestFirst(CostMatrixGraph& graph, std::vector<int>& bestPath);
private:
    static int calculateBound(CostMatrixGraph& graph, bool visited[], int currentCost);
    static void updateVisitedFromPath(std::vector<int>& path, bool visited[], int numOfCities);
};

#endif //TRAVELLING_SALESMAN_PROBLEM_BRANCHANDBOUNDTSPALGORITHMS_H
