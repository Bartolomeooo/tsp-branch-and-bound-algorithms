#ifndef SYMMETRICCOSTMATRIX_H
#define SYMMETRICCOSTMATRIX_H

#include <string>

class SymmetricCostMatrix {
private:
    int* costs; // Dynamic array for storing costs
    int numOfCities; // Number of vertices (cities)

    int index(int row, int col); // Calculate the index in the array for given row and column

public:
    SymmetricCostMatrix(); // Default constructor
    SymmetricCostMatrix(int numOfCities); // Constructor with number of vertices
    ~SymmetricCostMatrix(); // Destructor

    void printGraph(); // Print the cost matrix
    void setNumOfCities(int num); // Set the number of vertices
    int getNumOfCities(); // Get the number of vertices
    int getCost(int city1, int city2); // Get the cost between two cities
    void setCost(int city1, int city2, int cost); // Set the cost between two cities
    void addVertexes(int vertexes); // Allocate memory for the graph
    void fillGraphFromFile(std::string& filePath); // Fill the graph from a file
    void generateRandomCostMatrix(int numOfCities); // Generate a random symmetric cost matrix
};

#endif
