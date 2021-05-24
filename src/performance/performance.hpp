

#ifndef FEUP_CAL_PARKING_PERFORMANCE_HPP
#define FEUP_CAL_PARKING_PERFORMANCE_HPP

#include "../model/Graph/Graph.hpp"
#include "../model/StreetMap/StreetMap.h"

inline Graph<int> generateRandomGraph(unsigned size) {
    Graph<int> graph{};
    id_t nodeId = 1;
    for (unsigned i = 0; i < size; ++i) {
        graph.addNode(nodeId++, rand() % (10 * size));
    }
    id_t edgeId = 1;
    for (Node<int> *node : graph.getNodes()) {
        node->addEdge(edgeId++, graph.findNodeById(rand() % graph.getNumberOfNodes() + 1), rand() % (10 * size));
    }
    return graph;
}

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

void testPerformanceKosaraju(unsigned iterations, unsigned minSize, unsigned maxSize, unsigned step);

void testPerformanceBfs(unsigned iterations, unsigned minSize, unsigned maxSize, unsigned step);

void testPerformanceDfs(unsigned iterations, unsigned minSize, unsigned maxSize, unsigned step);

void testPerformanceDijkstra(unsigned iterations, unsigned minSize, unsigned maxSize, unsigned step);

void testPerformanceAStar(unsigned iterations, unsigned minSize, unsigned maxSize, unsigned step);

void testPerformanceFloydWarshall(unsigned iterations, unsigned minSize, unsigned maxSize, unsigned step);

#endif //FEUP_CAL_PARKING_PERFORMANCE_HPP
