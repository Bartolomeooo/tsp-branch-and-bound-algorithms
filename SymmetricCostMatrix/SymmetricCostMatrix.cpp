#include "SymmetricCostMatrix.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Default constructor
SymmetricCostMatrix::SymmetricCostMatrix() {
    numOfCities = 0;
    costs = nullptr;
}

// Constructor with the number of cities
SymmetricCostMatrix::SymmetricCostMatrix(int numOfCities) {
    this->numOfCities = numOfCities;
    int size = (numOfCities * (numOfCities + 1)) / 2; // Allocate memory for the lower triangular part
    costs = new int[size];
}

// Destructor
SymmetricCostMatrix::~SymmetricCostMatrix() {
    delete[] costs; // Free allocated memory
}

// Print the graph
void SymmetricCostMatrix::printGraph() {
    if (numOfCities == 0) {
        cout << "Graph is empty!" << endl;
        return;
    }
    cout << "Symmetric Cost Matrix:" << endl;
    for (int i = 0; i < numOfCities; i++) {
        for (int j = 0; j < numOfCities; j++) {
            cout << setw(5) << getCost(i, j); // Use `getCost` to access values symmetrically
        }
        cout << endl;
    }
    cout << endl;
}

// Set the number of cities
void SymmetricCostMatrix::setNumOfCities(int num) {
    this->numOfCities = num;
}

// Get the number of cities
int SymmetricCostMatrix::getNumOfCities() {
    return numOfCities;
}

// Get the cost between two cities
int SymmetricCostMatrix::getCost(int city1, int city2) {
    if (city1 > city2) swap(city1, city2); // Ensure city1 <= city2
    return costs[index(city1, city2)];
}

// Set the cost between two cities
void SymmetricCostMatrix::setCost(int city1, int city2, int cost) {
    if (city1 > city2) swap(city1, city2); // Ensure city1 <= city2
    costs[index(city1, city2)] = cost;
}

// Allocate memory for the graph
void SymmetricCostMatrix::addVertexes(int vertexes) {
    numOfCities = vertexes;
    delete[] costs; // Free existing memory
    costs = new int[(vertexes * (vertexes + 1)) / 2]; // Allocate new memory for the matrix
}

// Fill the graph with data from a file
void SymmetricCostMatrix::fillGraphFromFile(string& filePath) {
    ifstream inFile(filePath);

    if (inFile.is_open()) {
        inFile >> numOfCities; // Read the number of cities
        addVertexes(numOfCities); // Allocate memory for the matrix

        for (int i = 0; i < numOfCities; i++) {
            for (int j = 0; j < numOfCities; j++) {
                int cost;
                inFile >> cost;

                // Store only the lower triangular part
                if (j <= i) {
                    setCost(i, j, cost);
                }
            }
        }

        cout << "Successfully filled symmetric cost matrix!" << endl;
        inFile.close();
    } else {
        cerr << "Cannot open file: " << filePath << endl;
    }
}

// Generate a random symmetric cost matrix
void SymmetricCostMatrix::generateRandomCostMatrix(int numOfCities) {
    setNumOfCities(numOfCities);
    addVertexes(numOfCities);

    for (int i = 0; i < numOfCities; i++) {
        for (int j = 0; j <= i; j++) { // Generate costs for the lower triangular part
            int cost = (i == j) ? -1 : rand() % 100 + 1; // Diagonal elements are -1
            setCost(i, j, cost);
        }
    }
}

// Calculate the index in the one-dimensional array
int SymmetricCostMatrix::index(int row, int col) {
    if (row > col) swap(row, col); // Ensure row <= col
    return (col * (col + 1)) / 2 + row; // Correct index calculation
}
