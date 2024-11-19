#ifndef _COST_MATRIX_GRAPH_H_
#define _COST_MATRIX_GRAPH_H_

#include <string>

class CostMatrixGraph {
private:
    int **graph; // Two-dimensional array representing the cost matrix
    int numOfVertexes; // Number of cities (vertices) in the graph

public:
    CostMatrixGraph(); // Constructor
    ~CostMatrixGraph(); // Destructor
    void printGraph(); // Print the cost matrix
    void setNumOfVertexes(int); // Set the number of vertices (cities)
    int getNumOfVertexes(); // Get the number of vertices (cities)
    int findElement(int, int); // Return the value from the cost matrix
    void setElement(int i, int j, int value); // Set value in the cost matrix
    void addVertexes(int); // Allocate memory for the cost matrix based on the number of vertices
    void fillGraphFromFile(std::string &filePath); // Fill the cost matrix from a file
    void generateRandomCostMatrix(int numOfCities); // Fill the cost matrix with numbers between 1-100
};

#endif
