
#ifndef FEUP_CAL_PARKING_SHORTESTDISTANCE_PERFORMANCE_HPP
#define FEUP_CAL_PARKING_SHORTESTDISTANCE_PERFORMANCE_HPP

#include "../model/StreetMap/StreetMap.h"
#include "../algorithms/shortestdistance.hpp"

inline Graph<MapPoint> generateRandomMap(unsigned size) {
    Graph<MapPoint> graph{};
    id_t nodeId = 1;
    for (unsigned i = 0; i < size; ++i) {
        MapPoint point(rand() % (10 * size), rand() % (10 * size));
        graph.addNode(nodeId++, point);
    }
    id_t edgeId = 1;
    for (Node<MapPoint> *node : graph.getNodes()) {
        node->addEdge(edgeId++, graph.findNodeById(rand() % graph.getNumberOfNodes() + 1), rand() % (10 * size));
    }
    return graph;
}

void testPerformanceDijkstra(unsigned iterations, unsigned minSize, unsigned maxSize, unsigned step) {
    std::ofstream csv("src/performance/results/dijkstra.csv");
    for (unsigned size = minSize; size < maxSize; size += step) {
        auto elapsed = std::chrono::duration<double>::zero();
        for (unsigned k = 0; k < iterations; ++k) {
            Graph<MapPoint> graph = generateRandomMap(size);
            MapPoint point = (graph.findNodeById(rand() % graph.getNumberOfNodes() + 1))->getElement();
            auto start = std::chrono::high_resolution_clock::now();
            dijkstra(point, graph);
            auto end = std::chrono::high_resolution_clock::now();
            elapsed += (end - start);
        }
        csv << size << "," << (elapsed.count() / iterations) << "\n";
    }
}

void testPerformanceAStar(unsigned iterations, unsigned minSize, unsigned maxSize, unsigned step) {
    std::ofstream csv("src/performance/results/astar.csv");
    for (unsigned size = minSize; size < maxSize; size += step) {
        auto elapsed = std::chrono::duration<double>::zero();
        for (unsigned k = 0; k < iterations; ++k) {
            Graph<MapPoint> graph = generateRandomMap(size);
            MapPoint origin = (graph.findNodeById(rand() % graph.getNumberOfNodes() + 1))->getElement();
            MapPoint target = (graph.findNodeById(rand() % graph.getNumberOfNodes() + 1))->getElement();
            auto start = std::chrono::high_resolution_clock::now();
            AStar(origin, graph, target);
            auto end = std::chrono::high_resolution_clock::now();
            elapsed += (end - start);
        }
        csv << size << "," << (elapsed.count() / iterations) << "\n";
    }
}

void testPerformanceFloydWarshall(unsigned iterations, unsigned minSize, unsigned maxSize, unsigned step) {
    std::ofstream csv("src/performance/results/floydwarshall.csv");
    for (unsigned size = minSize; size < maxSize; size += step) {
        auto elapsed = std::chrono::duration<double>::zero();
        for (unsigned k = 0; k < iterations; ++k) {
            Graph<MapPoint> graph = generateRandomMap(size);
            auto start = std::chrono::high_resolution_clock::now();
            floydWarshall(graph);
            auto end = std::chrono::high_resolution_clock::now();
            elapsed += (end - start);
        }
        csv << size << "," << (elapsed.count() / iterations) << "\n";
    }
}


#endif //FEUP_CAL_PARKING_SHORTESTDISTANCE_PERFORMANCE_HPP
