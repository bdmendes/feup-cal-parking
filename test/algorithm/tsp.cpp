#include <gtest/gtest.h>
#include "../../src/model/Graph/Graph.h"
#include "../../src/algorithms/tsp.h"

TEST(nearestNeighbour, simpleGraph){
    Graph<int> g1;
    auto n1 = g1.addNode(1, 1);
    auto n2 = g1.addNode(2, 2);
    auto n3 = g1.addNode(3, 3);
    auto n4 = g1.addNode(4, 4);
    g1.addEdge(1, n1, n2, 1);
    g1.addEdge(2, n1, n3, 2);
    g1.addEdge(3, n3, n2, 2);
    g1.addEdge(4, n2, n3, 4);
    g1.addEdge(5, n2, n4, 2);
    g1.addEdge(6, n3, n4, 2);
    std::vector<Node<int>*> toVisit = {n2,n3};
    std::vector<Node<int>*> buf;
    EXPECT_EQ(7, tspNearestNeighbour(n1, toVisit, n4, buf));
    std::vector<Node<int>*> expectedBuf = {n2,n3};
    EXPECT_EQ(buf, expectedBuf);
}

TEST(nearestNeighbour, impossibleTravel){
    Graph<int> g1;
    auto n1 = g1.addNode(1, 1);
    auto n2 = g1.addNode(2, 2);
    auto n3 = g1.addNode(3, 3);
    auto n4 = g1.addNode(4, 4);
    g1.addEdge(1, n1, n2, 1);
    g1.addEdge(2, n1, n3, 2);
    g1.addEdge(3, n3, n2, 2);
    g1.addEdge(4, n2, n3, 4);
    g1.addEdge(5, n2, n4, 2);
    std::vector<Node<int>*> toVisit = {n2,n3};
    std::vector<Node<int>*> buf;
    EXPECT_THROW(tspNearestNeighbour(n1, toVisit, n4, buf), std::exception);
}

TEST(bruteForce, simpleGraph){
    Graph<int> g1;
    auto n1 = g1.addNode(1, 1);
    auto n2 = g1.addNode(2, 2);
    auto n3 = g1.addNode(3, 3);
    auto n4 = g1.addNode(4, 4);
    g1.addEdge(1, n1, n2, 1);
    g1.addEdge(2, n1, n3, 2);
    g1.addEdge(3, n3, n2, 2);
    g1.addEdge(4, n2, n3, 4);
    g1.addEdge(5, n2, n4, 2);
    g1.addEdge(6, n3, n4, 2);
    std::vector<Node<int>*> toVisit = {n2,n3};
    std::vector<Node<int>*> buf;
    EXPECT_EQ(6, tspBruteForce(n1, toVisit, n4, buf));
    std::vector<Node<int>*> expectedBuf = {n3,n2};
    EXPECT_EQ(buf, expectedBuf);
}

TEST(bruteForce, impossibleTravel){
    Graph<int> g1;
    auto n1 = g1.addNode(1, 1);
    auto n2 = g1.addNode(2, 2);
    auto n3 = g1.addNode(3, 3);
    auto n4 = g1.addNode(4, 4);
    g1.addEdge(1, n1, n2, 1);
    g1.addEdge(2, n1, n3, 2);
    g1.addEdge(3, n3, n2, 2);
    g1.addEdge(4, n2, n3, 4);
    std::vector<Node<int>*> toVisit = {n2,n3};
    std::vector<Node<int>*> buf;
    EXPECT_THROW(tspBruteForce(n1, toVisit, n4, buf), std::exception);
}
