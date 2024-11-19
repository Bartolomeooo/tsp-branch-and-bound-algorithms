#include "Config.h"
#include "TSPSolver.h"

int main() {
    Config configManager;
    ConfigData config = configManager.loadConfig("config.txt");

    TSPSolver solver;
    solver.run(config);

    return 0;
}
