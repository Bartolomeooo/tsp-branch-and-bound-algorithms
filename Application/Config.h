#ifndef TRAVELLING_SALESMAN_PROBLEM_CONFIG_H
#define TRAVELLING_SALESMAN_PROBLEM_CONFIG_H


#include <string>

struct ConfigData {
    std::string algorithm;
    std::string matrixFile;
    int iterations;
    bool randomData;
    bool symmetricMatrix;
    int numCities;
    bool progressInfo;
};

class Config {
public:
    ConfigData loadConfig(const std::string& configFile);
    static void saveResultsToCSV(std::string& algorithm, bool symmetric,  int numCities, int iterations, double avgTime, double avgCost);
};


#endif //TRAVELLING_SALESMAN_PROBLEM_CONFIG_H
