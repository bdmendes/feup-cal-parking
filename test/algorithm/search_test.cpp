#include <gtest/gtest.h>
#include "../../src/model/Graph/Graph.hpp"
#include "../../src/algorithms/search.hpp"

TEST(kosajaru, strong) {
    Graph<int> g1;
    auto n0 = g1.addNode(1, 0);
    auto n1 = g1.addNode(2, 1);
    auto n2 = g1.addNode(3, 2);
    auto n3 = g1.addNode(4, 3);
    auto n4 = g1.addNode(5, 4);
    g1.addEdge(1, n0, n1, 0);
    g1.addEdge(2, n1, n2, 0);
    g1.addEdge(3, n2, n4, 0);
    g1.addEdge(4, n4, n2, 0);
    g1.addEdge(5, n2, n3, 0);
    g1.addEdge(6, n3, n0, 0);
    EXPECT_TRUE(kosaraju(g1));
}

TEST(kosajaru, not_strong) {
    Graph<int> g1;
    auto n0 = g1.addNode(1, 0);
    auto n1 = g1.addNode(2, 1);
    auto n2 = g1.addNode(3, 2);
    auto n3 = g1.addNode(4, 3);
    g1.addEdge(1, n0, n1, 0);
    g1.addEdge(2, n1, n2, 0);
    g1.addEdge(3, n3, n0, 0);
    g1.addEdge(4, n3, n2, 0);
    EXPECT_FALSE(kosaraju(g1));
}