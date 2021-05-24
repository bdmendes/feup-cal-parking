
#ifndef FEUP_CAL_PARKING_SEARCH_PERFORMANCE_HPP
#define FEUP_CAL_PARKING_SEARCH_PERFORMANCE_HPP

 Graph<int> generateRandomGraph(unsigned size) {
    Graph<int> graph{};
    id_t nodeId = 1;
    for (unsigned i = 0; i < size; ++i) {
        graph.addNode(nodeId++, rand() % (10 * size));
    }
    id_t edgeId = 1;
    for (Node<int> *node : graph.getNodes()) {
        id_t id = rand() % graph.getNumberOfNodes() + 1;
        node->addEdge(edgeId++, graph.findNodeById(id), rand() % (10 * size));
    }
    return graph;
}

void testPerformanceKosaraju(unsigned iterations, unsigned minSize, unsigned maxSize, unsigned step) {
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

#endif //FEUP_CAL_PARKING_SEARCH_PERFORMANCE_HPP
