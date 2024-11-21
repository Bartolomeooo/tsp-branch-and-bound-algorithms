cmake_minimum_required(VERSION 3.29)
project(TSP_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(travelling_salesman_problem
        CostMatrixGraph/CostMatrixGraph.cpp
        CostMatrixGraph/CostMatrixGraph.h
        main.cpp
        Application/TSPSolver.cpp
        Application/TSPSolver.h
        Application/Config.cpp
        Application/Config.h
        TSPAlgorithms/BranchAndBoundTSPAlgorithms.cpp
        TSPAlgorithms/BranchAndBoundTSPAlgorithms.h
        Application/Config.h
        PriorityQueue/PriorityQueue.cpp
        PriorityQueue/PriorityQueue.h
        Utils/AlgorithmUtils.cpp
        Utils/AlgorithmUtils.h
        Stack/Stack.cpp
        Stack/Stack.h
        SymmetricCostMatrix/SymmetricCostMatrix.cpp
        SymmetricCostMatrix/SymmetricCostMatrix.h)

target_include_directories(travelling_salesman_problem PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/CostMatrixGraph
        ${CMAKE_CURRENT_SOURCE_DIR}/TSPAlgorithms
        ${CMAKE_CURRENT_SOURCE_DIR}/Application
        ${CMAKE_CURRENT_SOURCE_DIR}/Utils
        ${CMAKE_CURRENT_SOURCE_DIR}/PriorityQueue
        ${CMAKE_CURRENT_SOURCE_DIR}/Stack
        ${CMAKE_CURRENT_SOURCE_DIR}/SymmetricCostMatrix
)

#set(CMAKE_EXE_LINKER_FLAGS "-static")