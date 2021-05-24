#include <gtest/gtest.h>
#include "../../src/model/Graph/Graph.hpp"
#include "../../src/model/StreetMap/StreetMap.h"
#include "../../src/algorithms/shortestdistance.hpp"

TEST(dijkstra, simpleGraph){
    Graph<int> g1;
    auto n1 = g1.addNode(1, 1);
    auto n2 = g1.addNode(2, 2);
    auto n3 = g1.addNode(3, 3);
    auto n4 = g1.addNode(4, 4);
    auto n5 = g1.addNode(5, 5);
    auto n6 = g1.addNode(6, 6);
    g1.addEdge(1, n1, n2, 1);
    g1.addEdge(2, n1, n3, 2);
    g1.addEdge(3, n3, n2, 2);
    g1.addEdge(4, n2, n3, 4);
    g1.addEdge(5, n2, n4, 2);
    g1.addEdge(6, n3, n4, 2);
    g1.addEdge(7, n4, n5, 1);
    g1.addEdge(8, n4, n6, 3);
    g1.addEdge(9, n5, n6, 3);
    std::vector<Node<int>*> expectedPath = {n1,n2,n4,n6};
    double expectedDistance = 6;
    dijkstra(n1->getElement(), g1);
    auto path = getDijkstraPath(g1, n1->getElement(), n6->getElement());
    EXPECT_EQ(path, expectedPath);
    EXPECT_EQ(distance(path), expectedDistance);
}

TEST(dijkstra, impossibleTravel){
    Graph<int> g1;
    auto n1 = g1.addNode(1, 1);
    auto n2 = g1.addNode(2, 2);
    auto n3 = g1.addNode(3, 3);
    auto n4 = g1.addNode(4, 4);
    auto n5 = g1.addNode(5, 5);
    auto n6 = g1.addNode(6, 6);
    g1.addEdge(1, n1, n2, 1);
    g1.addEdge(2, n1, n3, 2);
    g1.addEdge(3, n3, n2, 2);
    g1.addEdge(4, n2, n3, 4);
    g1.addEdge(5, n2, n4, 2);
    g1.addEdge(6, n3, n4, 2);
    g1.addEdge(7, n4, n5, 1);
    g1.addEdge(8, n6, n5, 3);
    dijkstra(n1->getElement(), g1);
    EXPECT_THROW(getDijkstraPath(g1, n1->getElement(), n6->getElement()), std::exception);
}

TEST(floydWarshall, multiplePaths){
    Graph<MapPoint> g1;
    auto n1 = g1.addNode(1, MapPoint(0.1,0.1));
    auto n2 = g1.addNode(2, MapPoint(0.11,0.11));
    auto n3 = g1.addNode(3, MapPoint(0.12,0.12));
    auto n4 = g1.addNode(4, MapPoint(0.13,0.13));
    auto n5 = g1.addNode(5, MapPoint(0.14,0.14));
    auto n6 = g1.addNode(6, MapPoint(0.15,0.15));
    auto n7 = g1.addNode(7, MapPoint(0.16,0.16));
    g1.addEdge(1, n1, n2, 1);
    g1.addEdge(2, n1, n3, 2);
    g1.addEdge(3, n3, n2, 2);
    g1.addEdge(4, n2, n3, 4);
    g1.addEdge(5, n2, n4, 2);
    g1.addEdge(6, n3, n4, 2);
    g1.addEdge(7, n4, n5, 1);
    g1.addEdge(8, n5, n6, 3);
    g1.addEdge(9, n5, n7, 1);
    g1.addEdge(10, n7, n6, 1);
    auto paths = floydWarshall(g1);

    auto path1To4 = paths.at(1).at(4);
    std::vector<Node<MapPoint>*> expected1To4 = {n2};
    EXPECT_EQ(expected1To4, path1To4);

    auto path1To6 = paths.at(1).at(6);
    std::vector<Node<MapPoint>*> expected1To6 = {n2,n4,n5,n7};
    EXPECT_EQ(expected1To6, path1To6);
}
