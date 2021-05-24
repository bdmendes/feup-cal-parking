#include <iostream>
#include <fstream>

#include "model/Graph/Graph.hpp"
#include "model/StreetMap/StreetMap.h"
#include "algorithms/search.hpp"
#include "controller/parkselector.h"
#include "algorithms/shortestdistance.hpp"
#include "performance/search_performance.cpp"
#include "performance/shortestdistance_performance.cpp"

template<class T>
void describeGraph(Graph<T> &g) {
    std::cout << "START DESCRIBING\n";
    for (auto n: g.getNodes()) {
        std::cout << n->getElement() << ", adjacent with: ";
        for (auto nn: n->getAdjacent()) {
            std::cout << nn->getTarget()->getElement() << "(w" << nn->getWeight() << ") ";
        }
        std::cout << "\n";
    }
    std::cout << "END DESCRIBING\n\n";
}

int main() {
    std::srand(std::time(nullptr));
    std::string nodesXY("maps/porto/porto_strong_nodes_xy.txt");
    std::string nodesLL("maps/porto/porto_strong_nodes_latlng.txt");
    std::string edges("maps/porto/porto_strong_edges.txt");
    StreetMap map(1900, 1000);
    map.readFromFile(nodesXY, nodesLL, edges);

    /* Assemble actual path */
    std::vector<Node<MapPoint>*> stopPoints;
    auto source = map.findNodeById(37);
    auto target = map.findNodeById(124);
    auto p1 = map.findNodeById(67);
    auto p2 = map.findNodeById(89);
    if (!source || !target || !p1 || !p2){
        throw std::logic_error("Nodes not found");
    }
    stopPoints.push_back(p1);
    stopPoints.push_back(p2);
    auto path = getPathAfterParkReplacement(map, stopPoints, target, {true, true}, 0.5, 0.3, 0.2, 200);
    auto walkPaths = getWalkPaths(map, stopPoints, path);
    std::vector<Node<MapPoint>*> fullPath;
    fullPath.push_back(source);
    for (const auto& p : path) fullPath.push_back(p);
    fullPath.push_back(target);

    /* Assemble paths */
    std::vector<std::vector<Node<MapPoint>*>> describedPaths;
    double totalDistance = 0;
    for (int i = 0; i < fullPath.size()-1; i++){
        AStar(fullPath.at(i)->getElement(), map, fullPath.at(i+1)->getElement());
        auto p = getAStarPath(map, fullPath.at(i)->getElement(), fullPath.at(i+1)->getElement());
        totalDistance += distance(p);
    }

    std::cout << totalDistance << std::flush;

    testPerformanceKosaraju(5, 100, 10100, 1000);
    testPerformanceBfs(5, 100, 10100, 1000);
    testPerformanceDfs(5, 100, 10100, 1000);
    testPerformanceDijkstra(5, 100, 10100, 1000);
    testPerformanceAStar(5, 100, 10100, 1000);
    testPerformanceFloydWarshall(5, 100, 500, 100);

    map.showGraph();
}
