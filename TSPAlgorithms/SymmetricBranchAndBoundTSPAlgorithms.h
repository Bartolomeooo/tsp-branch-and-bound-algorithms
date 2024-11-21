#ifndef SYMMETRICBRANCHANDBOUNDTSPALGORITHMS_H
#define SYMMETRICBRANCHANDBOUNDTSPALGORITHMS_H

#include "SymmetricCostMatrix.h"
#include <vector>

class SymmetricBranchAndBoundTSPAlgorithms {
public:
    // BFS-based Branch and Bound TSP algorithm for symmetric matrices
    static int branchAndBoundBFS(SymmetricCostMatrix& graph, std::vector<int>& bestPath);

    // DFS-based Branch and Bound TSP algorithm for symmetric matrices
    static int branchAndBoundDFS(SymmetricCostMatrix& graph, std::vector<int>& bestPath);

    // Best-First Search-based Branch and Bound TSP algorithm for symmetric matrices
    static int branchAndBoundBestFirst(SymmetricCostMatrix& graph, std::vector<int>& bestPath);
};

#endif //SYMMETRICBRANCHANDBOUNDTSPALGORITHMS_H
