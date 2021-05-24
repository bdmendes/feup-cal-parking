#include "model/Graph/Graph.hpp"
#include "ui/menu/menu.h"
#include "model/StreetMap/StreetMap.h"
#include "algorithms/search.hpp"
#include "algorithms/shortestdistance.hpp"
#include "performance/performance.h"


int main() {
    std::srand(std::time(nullptr));
    StreetMap map(1900, 1000);
    /*Menu introMenu(map);
    introMenu.show();*/
    testPerformanceBruteForce(5, 20, 30, 2);
    testPerformanceNearestNeighbour(5, 10, 500, 25);
    testPerformanceFloydWarshall(5, 100, 300, 25);
    testPerformanceAStar(5, 100, 10000, 500);
    testPerformanceDijkstra(5, 100, 10000, 500);
    testPerformanceDfs(5, 100, 10000, 500);
    testPerformanceBfs(5, 100, 10000, 500);
    testPerformanceKosaraju(5, 100, 10000, 500);
}
