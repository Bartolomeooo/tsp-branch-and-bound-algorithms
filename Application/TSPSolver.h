#ifndef TRAVELLING_SALESMAN_PROBLEM_TSPSOLVER_H
#define TRAVELLING_SALESMAN_PROBLEM_TSPSOLVER_H


#include "CostMatrixGraph.h"
#include "SymmetricCostMatrix.h"
#include "Config.h"
#include "BranchAndBoundTSPAlgorithms.h"
#include "SymmetricBranchAndBoundTSPAlgorithms.h"

class TSPSolver {
public:
    void run(ConfigData& config);
};


#endif
