#ifndef TRAVELLING_SALESMAN_PROBLEM_BRANCHANDBOUNDTSPALGORITHMS_H
#define TRAVELLING_SALESMAN_PROBLEM_BRANCHANDBOUNDTSPALGORITHMS_H

#include "CostMatrixGraph.h"
#include <vector>

class BranchAndBoundTSPAlgorithms {
public:
    // BFS-based Branch and Bound TSP algorithm (to be implemented)
    static int branchAndBoundBFS(CostMatrixGraph& graph, std::vector<int>& bestPath);

    // DFS-based Branch and Bound TSP algorithm (to be implemented)
    static int branchAndBoundDFS(CostMatrixGraph& graph, std::vector<int>& bestPath);

    // Best-First Search-based Branch and Bound TSP algorithm (to be implemented)
    static int branchAndBoundBestFirst(CostMatrixGraph& graph, std::vector<int>& bestPath);
};

#endif //TRAVELLING_SALESMAN_PROBLEM_BRANCHANDBOUNDTSPALGORITHMS_H
