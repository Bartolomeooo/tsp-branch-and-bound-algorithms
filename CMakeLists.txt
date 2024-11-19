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
        Application/Config.h)

target_include_directories(travelling_salesman_problem PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/CostMatrixGraph
        ${CMAKE_CURRENT_SOURCE_DIR}/TSPAlgorithms
        ${CMAKE_CURRENT_SOURCE_DIR}/Application
)

#set(CMAKE_EXE_LINKER_FLAGS "-static")