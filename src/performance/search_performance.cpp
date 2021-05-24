
#ifndef FEUP_CAL_PARKING_SEARCH_PERFORMANCE_CPP
#define FEUP_CAL_PARKING_SEARCH_PERFORMANCE_CPP

#include "performance.hpp"
#include "../algorithms/search.hpp"
#include <chrono>
#include <fstream>

inline void testPerformanceKosaraju(unsigned iterations, unsigned minSize, unsigned maxSize, unsigned step) {
    std::ofstream csv("src/performance/results/kosaraju.csv");
    for (unsigned size = minSize; size < maxSize; size += step) {
        auto elapsed = std::chrono::duration<double>::zero();
        for (unsigned k = 0; k < iterations; ++k) {
            Graph<int> graph = generateRandomGraph(size);
            auto start = std::chrono::high_resolution_clock::now();
            kosaraju(graph);
            auto end = std::chrono::high_resolution_clock::now();
            elapsed += (end - start);
        }
        csv << size << "," << (elapsed.count() / iterations) << "\n";
    }
}

inline void testPerformanceBfs(unsigned iterations, unsigned minSize, unsigned maxSize, unsigned step) {
    std::ofstream csv("src/performance/results/bfs.csv");
    for (unsigned size = minSize; size < maxSize; size += step) {
        auto elapsed = std::chrono::duration<double>::zero();
        for (unsigned k = 0; k < iterations; ++k) {
            Graph<int> graph = generateRandomGraph(size);
            Node<int>* source = graph.findNodeById(rand() % graph.getNumberOfNodes() + 1);
            auto start = std::chrono::high_resolution_clock::now();
            bfs(source, {}, graph);
            auto end = std::chrono::high_resolution_clock::now();
            elapsed += (end - start);
        }
        csv << size << "," << (elapsed.count() / iterations) << "\n";
    }
}

inline void testPerformanceDfs(unsigned iterations, unsigned minSize, unsigned maxSize, unsigned step) {
    std::ofstream csv("src/performance/results/dfs.csv");
    for (unsigned size = minSize; size < maxSize; size += step) {
        auto elapsed = std::chrono::duration<double>::zero();
        for (unsigned k = 0; k < iterations; ++k) {
            Graph<int> graph = generateRandomGraph(size);
            auto start = std::chrono::high_resolution_clock::now();
            dfsAll({}, graph);
            auto end = std::chrono::high_resolution_clock::now();
            elapsed += (end - start);
        }
        csv << size << "," << (elapsed.count() / iterations) << "\n";
    }
}

#endif //FEUP_CAL_PARKING_SEARCH_PERFORMANCE_CPP
