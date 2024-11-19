#include "Config.h"
#include <fstream>
#include <iostream>

// Load configuration from the file
ConfigData Config::loadConfig(const std::string& configFile) {
    ConfigData config;
    std::ifstream inFile(configFile);

    if (inFile.is_open()) {
        std::string line;
        // Read each line in the configuration file
        while (std::getline(inFile, line)) {
            // Ignore lines that start with '#'
            if (line.empty() || line[0] == '#') {
                continue;
            }
            size_t pos = line.find('=');
            // Parse the key and value
            if (pos != std::string::npos) {
                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + 1);

                // Map keys to appropriate configuration fields
                if (key == "algorithm") {
                    config.algorithm = value;
                } else if (key == "matrix_file") {
                    config.matrixFile = value;
                } else if (key == "iterations") {
                    config.iterations = std::stoi(value);
                } else if (key == "random_data") {
                    config.randomData = (value == "true");
                } else if (key == "num_cities") {
                    config.numCities = std::stoi(value);
                } else if (key == "progress_info") {
                    config.progressInfo = (value == "true");
                }
            }
        }
        inFile.close();
    } else {
        std::cerr << "Unable to open config file: " << configFile << std::endl;
    }
    return config;
}

// Save the results to an appropriate CSV file based on the algorithm
void Config::saveResultsToCSV(std::string& algorithm, int numCities, int iterations, double avgTime, double avgCost) {
    std::string filename;

    // Select the file name based on the algorithm type
    if (algorithm == "branch_and_bound_bfs") {
        filename = "branch_and_bound_bfs_results.csv";
    } else if (algorithm == "branch_and_bound_dfs") {
        filename = "branch_and_bound_dfs_results.csv";
    } else if (algorithm == "branch_and_bound_best_first") {
        filename = "branch_and_bound_best_first_results.csv";
    }

    std::ofstream outFile(filename, std::ios::app);

    if (outFile.is_open()) {
        outFile << algorithm << "," << numCities << "," << iterations << "," << avgTime << "\n";
        outFile.close();
    } else {
        // Error message if file cannot be opened
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}
