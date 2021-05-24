#include "performance.h"
#include "../algorithms/tsp.hpp"

void testPerformanceNearestNeighbour(unsigned iterations, unsigned minSize, unsigned maxSize, unsigned step) {
    std::ofstream csv("src/performance/results/nearestneighbour.csv");
    for (unsigned size = minSize; size < maxSize; size += step) {
        auto elapsed = std::chrono::duration<double>::zero();
        for (unsigned k = 0; k < iterations; ++k) {
            Graph<int> graph = generateRandomGraphConnected(size);
            std::vector<Node<int>*> intermediate{};
            std::vector<Node<int>*> found{};
            for (Node<int>* node : graph.getNodes()) {
                if (rand() % 5  == 0) {
                    intermediate.push_back(node);
                }
            }
            Node<int>* source = graph.findNodeById(rand() % graph.getNumberOfNodes() + 1);
            while (std::find(intermediate.begin(), intermediate.end(), source) != intermediate.end()) {
                source = graph.findNodeById(rand() % graph.getNumberOfNodes() + 1);
            }
            Node<int>* target = graph.findNodeById(rand() % graph.getNumberOfNodes() + 1);
            while (std::find(intermediate.begin(), intermediate.end(), target) != intermediate.end()) {
                target = graph.findNodeById(rand() % graph.getNumberOfNodes() + 1);
                while (source == target) {
                    target = graph.findNodeById(rand() % graph.getNumberOfNodes() + 1);
                }
            }
            while (source == target) {
                target = graph.findNodeById(rand() % graph.getNumberOfNodes() + 1);
            }
            auto start = std::chrono::high_resolution_clock::now();
            tspNearestNeighbour(source, intermediate, target, found);
            auto end = std::chrono::high_resolution_clock::now();
            elapsed += (end - start);
        }
        csv << size << "," << (elapsed.count() / iterations) << "\n";
    }
}
