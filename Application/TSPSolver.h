#ifndef TRAVELLING_SALESMAN_PROBLEM_TSPSOLVER_H
#define TRAVELLING_SALESMAN_PROBLEM_TSPSOLVER_H


#include "CostMatrixGraph.h"
#include "Config.h"
#include "TSPAlgorithms.h"
#include "BranchAndBoundTSPAlgorithms.h"

class TSPSolver {
public:
    void run(ConfigData& config);
};


#endif
