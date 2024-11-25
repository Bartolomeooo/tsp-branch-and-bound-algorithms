#ifndef SYMMETRICBRANCHANDBOUNDTSPALGORITHMS_H
#define SYMMETRICBRANCHANDBOUNDTSPALGORITHMS_H

#include "SymmetricCostMatrix.h"
#include <vector>

class SymmetricBranchAndBoundTSPAlgorithms {
public:
    static int branchAndBoundBFS(SymmetricCostMatrix& graph, std::vector<int>& bestPath);
    static int branchAndBoundDFS(SymmetricCostMatrix& graph, std::vector<int>& bestPath);
    static int branchAndBoundBestFirst(SymmetricCostMatrix& graph, std::vector<int>& bestPath);

private:
    static int calculateBound(SymmetricCostMatrix& graph, bool visited[], int currentCost);
    static void updateVisitedFromPath(std::vector<int>& path, bool visited[], int numOfCities);
};

#endif
