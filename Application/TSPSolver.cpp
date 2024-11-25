#include "TSPSolver.h"
#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;
using namespace chrono;

// Function to measure execution time of a given TSP algorithm
pair<int, long long> measureSymmetricExecutionTime(int(*algorithm)(SymmetricCostMatrix& graph, vector<int>&), SymmetricCostMatrix& graph, vector<int>& bestPath) {
    auto start = high_resolution_clock::now();
    int result = algorithm(graph, bestPath);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start).count();
    return make_pair(result, duration);
}

// Function to measure execution time of a given TSP algorithm
pair<int, long long> measureExecutionTime(int(*algorithm)(CostMatrixGraph&, vector<int>&), CostMatrixGraph& graph, vector<int>& bestPath) {
    auto start = high_resolution_clock::now();
    int result = algorithm(graph, bestPath);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start).count();
    return make_pair(result, duration);
}

void TSPSolver::run(ConfigData& config) {
    srand(time(NULL));  // Initialize random seed for random data generation
    vector<int> bestPath;  // Store the best path
    long long totalTime = 0;  // Total time for all iterations

    SymmetricCostMatrix symmetricGraph;
    CostMatrixGraph graph;

    graph.addVertexes(config.numCities);  // Set the number of cities
    symmetricGraph.addVertexes(config.numCities);


    // Load graph from file if not using random data
    if (!config.randomData) {
        graph.fillGraphFromFile(config.matrixFile);
        symmetricGraph.fillGraphFromFile(config.matrixFile);
    }

    int cost = -1;  // To store the cost of the best path

    // Iterate for the specified number of iterations
    for (int iteration = 0; iteration < config.iterations; ++iteration) {
        // If random data is used, generate a random cost matrix
        if (config.randomData) {
            graph.generateRandomCostMatrix(config.numCities);
            symmetricGraph.generateRandomCostMatrix(config.numCities);
        }

        // Select and run the algorithm based on configuration
        pair<int, long long> result;
        if(config.symmetricMatrix) {
            if (config.algorithm == "branch_and_bound_bfs") {
                result = measureSymmetricExecutionTime(SymmetricBranchAndBoundTSPAlgorithms::branchAndBoundBFS, symmetricGraph, bestPath);
            } else if (config.algorithm == "branch_and_bound_dfs") {
                result = measureSymmetricExecutionTime(SymmetricBranchAndBoundTSPAlgorithms::branchAndBoundDFS, symmetricGraph, bestPath);
            } else if (config.algorithm == "branch_and_bound_best_first") {
                result = measureSymmetricExecutionTime(SymmetricBranchAndBoundTSPAlgorithms::branchAndBoundBestFirst, symmetricGraph, bestPath);
            } else {
                cerr << "Unknown algorithm specified." << endl;
                return;
            }
        }
        else {
            if (config.algorithm == "branch_and_bound_bfs") {
                result = measureExecutionTime(BranchAndBoundTSPAlgorithms::branchAndBoundBFS, graph, bestPath);
            } else if (config.algorithm == "branch_and_bound_dfs") {
                result = measureExecutionTime(BranchAndBoundTSPAlgorithms::branchAndBoundDFS, graph, bestPath);
            } else if (config.algorithm == "branch_and_bound_best_first") {
                result = measureExecutionTime(BranchAndBoundTSPAlgorithms::branchAndBoundBestFirst, graph, bestPath);
            } else {
                cerr << "Unknown algorithm specified." << endl;
                return;
            }
        }

        // Update cost and total time
        cost = result.first;
        totalTime += result.second;

        // Display progress information if enabled
        if (config.progressInfo) {
            float progress = (static_cast<float>(iteration + 1) / config.iterations) * 100;
            cout << "Progress: " << fixed << setprecision(2) << progress << "% completed ("
                 << iteration + 1 << "/" << config.iterations << " iterations)." << endl;
        }
    }

    // Calculate the average time per iteration in milliseconds
    long double avgTime = static_cast<long double>(totalTime) / (1000000.0 * config.iterations);

    // Save the results to a CSV file
    Config appConfig;
    Config::saveResultsToCSV(config.algorithm, config.symmetricMatrix, config.numCities, config.iterations, avgTime, cost);

    cout << "Results saved to the file" << endl << endl;

    // Output the results if not using random data
    if (!config.randomData) {
        cout << "Best path: ";
        for (int city : bestPath) {
            cout << city << " ";
        }
        cout << endl;
        cout << "Average time: " << avgTime << " ms" << endl;
        cout << "Cost: " << cost << endl;
    } else {
        // Display average time for random data runs
        cout << "Average time for random data: " << avgTime << " ms" << endl;
    }
}
