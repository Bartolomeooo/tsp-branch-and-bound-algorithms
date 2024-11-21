#include "SymmetricCostMatrix.h"
#include <iostream>
#include <stdexcept>

// Constructor to initialize the cost matrix with the given number of cities
SymmetricCostMatrix::SymmetricCostMatrix(int numOfCities) : numOfCities(numOfCities) {
    // Allocate memory for the symmetric matrix, using the formula for a triangular number
    int size = (numOfCities * (numOfCities + 1)) / 2;
    costs = new int[size];
}

// Destructor to free dynamically allocated memory
SymmetricCostMatrix::~SymmetricCostMatrix() {
    delete[] costs;
}

// Set the cost between two cities
void SymmetricCostMatrix::setCost(int city1, int city2, int cost) {
    if (city1 >= numOfCities || city2 >= numOfCities || city1 < 0 || city2 < 0) {
        throw std::out_of_range("City index out of range");
    }
    int idx = index(city1, city2);
    costs[idx] = cost;
}

// Get the cost between two cities
int SymmetricCostMatrix::getCost(int city1, int city2) const {
    if (city1 >= numOfCities || city2 >= numOfCities || city1 < 0 || city2 < 0) {
        throw std::out_of_range("City index out of range");
    }
    int idx = index(city1, city2);
    return costs[idx];
}

// Get the number of cities in the matrix
int SymmetricCostMatrix::getNumOfCities() const {
    return numOfCities;
}

// Calculate the index for storing the cost between two cities in the dynamic array
int SymmetricCostMatrix::index(int row, int col) const {
    // Ensure row <= col for symmetry, as we're storing only the upper triangle
    if (row > col) {
        std::swap(row, col);
    }
    return (col * (col + 1)) / 2 + row;
}
