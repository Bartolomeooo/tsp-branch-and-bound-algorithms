#include "SymmetricCostMatrix.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

// Constructor to initialize the cost matrix with the given number of cities
SymmetricCostMatrix::SymmetricCostMatrix(int numOfCities) {
    this->numOfCities = numOfCities;
    int size = (numOfCities * (numOfCities + 1)) / 2;
    costs = new int[size];
}

// Destructor to free dynamically allocated memory
SymmetricCostMatrix::~SymmetricCostMatrix() {
    delete[] costs;
}

// Set the cost between two cities
void SymmetricCostMatrix::setCost(int city1, int city2, int cost) {
    if (city1 > city2) {
        std::swap(city1, city2);
    }
    costs[index(city1, city2)] = cost;
}

// Get the cost between two cities
int SymmetricCostMatrix::getCost(int city1, int city2) const {
    if (city1 > city2) {
        std::swap(city1, city2);
    }
    return costs[index(city1, city2)];
}

// Get the number of cities in the matrix
int SymmetricCostMatrix::getNumOfCities() const {
    return numOfCities;
}

// Fill the cost matrix from a file
void SymmetricCostMatrix::fillFromFile(const std::string& filePath) {
    ifstream inFile(filePath);

    if (inFile.is_open()) {
        inFile >> numOfCities;
        int size = (numOfCities * (numOfCities + 1)) / 2;
        delete[] costs;
        costs = new int[size];

        for (int i = 0; i < numOfCities; ++i) {
            for (int j = 0; j <= i; ++j) {
                int cost;
                inFile >> cost;
                setCost(i, j, cost);
            }
        }

        inFile.close();
    } else {
        cerr << "Cannot open file: " << filePath << endl;
    }
}

// Fill the cost matrix with random data
void SymmetricCostMatrix::fillRandom(int maxCost) {
    srand(time(0));
    for (int i = 0; i < numOfCities; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (i == j) {
                setCost(i, j, -1);  // No self-loop
            } else {
                int cost = rand() % maxCost + 1;
                setCost(i, j, cost);
            }
        }
    }
}

// Print the cost matrix
void SymmetricCostMatrix::printMatrix() const {
    for (int i = 0; i < numOfCities; ++i) {
        for (int j = 0; j < numOfCities; ++j) {
            if (i <= j) {
                cout << setw(5) << getCost(i, j);
            } else {
                cout << setw(5) << getCost(j, i);
            }
        }
        cout << endl;
    }
}

// Calculate the index for storing the cost between two cities in the dynamic array
int SymmetricCostMatrix::index(int row, int col) const {
    return (row * numOfCities) - (row * (row + 1)) / 2 + col;
}
