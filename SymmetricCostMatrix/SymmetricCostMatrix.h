#ifndef SYMMETRICCOSTMATRIX_H
#define SYMMETRICCOSTMATRIX_H
#include <string>


class SymmetricCostMatrix {
public:
    // Constructor to initialize the cost matrix with the given number of cities
    SymmetricCostMatrix(int numOfCities);

    // Destructor to free dynamically allocated memory
    ~SymmetricCostMatrix();

    // Set the cost between two cities
    void setCost(int city1, int city2, int cost);

    // Get the cost between two cities
    int getCost(int city1, int city2) const;

    // Get the number of cities in the matrix
    int getNumOfCities() const;

    // Fill the cost matrix from a file
    void fillFromFile(const std::string& filePath);

    // Fill the cost matrix with random data
    void fillRandom(int maxCost);

    // Print the cost matrix
    void printMatrix() const;

private:
    int numOfCities;     // Number of cities in the matrix
    int* costs;          // Pointer to dynamically allocated array storing costs

    // Calculate the index for storing the cost between two cities in the dynamic array
    int index(int row, int col) const;
};

#endif //SYMMETRICCOSTMATRIX_H
