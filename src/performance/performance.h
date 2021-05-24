
#ifndef FEUP_CAL_PARKING_PERFORMANCE_H
#define FEUP_CAL_PARKING_PERFORMANCE_H

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

inline Graph<int> generateRandomGraphConnected(unsigned size) {
    Graph<int> graph{};
    id_t nodeId = 1;
    for (unsigned i = 0; i < size; ++i) {
        graph.addNode(nodeId, nodeId);
        nodeId++;
    }
    id_t edgeId = 1;
    for (id_t i = 1; i <= graph.getNumberOfNodes(); ++i) {
        for (id_t j = 1; j <= graph.getNumberOfNodes(); ++j) {
            if (i == j) continue;
            graph.addEdge(edgeId++, graph.findNodeById(i), graph.findNodeById(j), rand() % (size * 10));
        }
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

void testPerformanceNearestNeighbour(unsigned iterations, unsigned minSize, unsigned maxSize, unsigned step);

#endif //FEUP_CAL_PARKING_PERFORMANCE_H
