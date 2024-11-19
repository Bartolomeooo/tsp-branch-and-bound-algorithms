#include<iostream>
#include<iomanip>
#include<fstream>
#include<climits>
#include<vector>
#include "CostMatrixGraph.h"

using namespace std;

// Initialize the graph with no vertices and null pointer
CostMatrixGraph::CostMatrixGraph() {
    numOfVertexes = 0;
    graph = nullptr;
}

// Free the dynamically allocated memory for the graph
CostMatrixGraph::~CostMatrixGraph() {
    for (int i = 0; i < numOfVertexes; i++) delete[] graph[i];
    delete[] graph;
}

// Function to print the graph
void CostMatrixGraph::printGraph() {
    if (numOfVertexes == 0) {
        cout << "Graph is empty!" << endl;
        return;
    }
    cout << "Cost matrix:" << endl;
    for (int i = 0; i < numOfVertexes; i++) {
        for (int j = 0; j < numOfVertexes; j++) {
            cout << setw(5) << graph[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

// Set the number of vertices in the graph
void CostMatrixGraph::setNumOfVertexes(int num) {
    this->numOfVertexes = num;
}

// Get the number of vertices in the graph
int CostMatrixGraph::getNumOfVertexes() {
    return numOfVertexes;
}

// Find and return the cost between vertex n and vertex m in the graph
int CostMatrixGraph::findElement(int n, int m) {
    return graph[n][m];
}

// Allocate memory for the graph based on the number of vertices
void CostMatrixGraph::addVertexes(int vertexes) {
    this->numOfVertexes = vertexes;
    this->graph = new int*[vertexes];
    for (int i = 0; i < vertexes; i++) {
        this->graph[i] = new int[vertexes];
    }
}

// Fill the graph with data from a file
void CostMatrixGraph::fillGraphFromFile(string& filePath) {
    ifstream inFile(filePath);

    if (inFile.is_open()) {
        int vertexes;
        inFile >> vertexes;
        this->addVertexes(vertexes);

        // Read the cost matrix from the file
        for (int i = 0; i < vertexes; i++) {
            for (int j = 0; j < vertexes; j++) {
                inFile >> graph[i][j];
            }
        }
        cout << "Successfully filled cost matrix!" << endl;
        inFile.close();
    } else {
        cerr << "Cannot open file: " << filePath << endl;
    }
}

// Set a specific value in the graph matrix at position (i, j)
void CostMatrixGraph::setElement(int i, int j, int value) {
    if (i >= 0 && i < numOfVertexes && j >= 0 && j < numOfVertexes) {
        graph[i][j] = value;
    } else {
        std::cerr << "Index out of bounds" << std::endl;
    }
}

// Generate a random cost matrix for a given number of cities
void CostMatrixGraph::generateRandomCostMatrix(int numOfCities) {
    // Set the number of vertices only if the matrix is empty; otherwise, overwrite the existing matrix
    if (numOfVertexes != numOfCities) {
        setNumOfVertexes(numOfCities);
        addVertexes(numOfCities);  // Reallocate memory if the number of vertices changes
    }

    srand(time(0));  // Seed the random number generator

    // Overwrite values in the existing matrix
    for (int i = 0; i < numOfCities; i++) {
        for (int j = 0; j < numOfCities; j++) {
            if (i == j) {
                graph[i][j] = -1;  // The cost from a city to itself is set to -1
            } else {
                graph[i][j] = rand() % 100 + 1;  // Random cost between 1 and 100
            }
        }
    }
}
