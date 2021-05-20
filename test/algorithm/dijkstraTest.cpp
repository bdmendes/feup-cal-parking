#include <gtest/gtest.h>
#include "../../src/model/Graph/Graph.h"
#include "../../src/algorithms/dijkstra.h"

Graph<int> createTestGraph() {
    Graph<int> myGraph;

    for(int i = 1; i <= 7; i++)
        myGraph.addNode(i, i);

    myGraph.addEdge(1, 2, 2);
    myGraph.addEdge(1, 4, 7);
    myGraph.addEdge(2, 4, 3);
    myGraph.addEdge(2, 5, 5);
    myGraph.addEdge(3, 1, 2);
    myGraph.addEdge(3, 6, 5);
    myGraph.addEdge(4, 3, 1);
    myGraph.addEdge(4, 5, 1);
    myGraph.addEdge(4, 6, 6);
    myGraph.addEdge(4, 7, 4);
    myGraph.addEdge(5, 7, 2);
    myGraph.addEdge(6, 4, 3);
    myGraph.addEdge(7, 6, 4);

    return myGraph;
}

template <class T>
void checkAllPaths(Graph<T> &g, std::string expected) {
    std::stringstream ss;
    std::vector<Node<T>* > vs = g.getNodes();
    for(unsigned int i = 0; i < vs.size(); i++) {
        ss << vs[i]->getElement() << "<-";
        if ( vs[i]->getPath() != NULL )
            ss << vs[i]->getPath()->getInfo();
        ss << "|";
    }
    EXPECT_EQ(expected, ss.str());
}

template <class T>
void checkSinglePath(std::vector<T> path, std::string expected) {
    std::stringstream ss;
    for(unsigned int i = 0; i < path.size(); i++)
        ss << path[i] << " ";
    EXPECT_EQ(expected, ss.str());
}

TEST(dijkstraTest, dijkstra){
    Graph<int> graph = createTestGraph();
    dijkstra(3, graph);
    checkAllPaths(graph, "1<-3|2<-1|3<-|4<-2|5<-4|6<-3|7<-5|");

    dijkstra(1, graph);
    checkAllPaths(graph, "1<-|2<-1|3<-4|4<-2|5<-4|6<-4|7<-5|");
    //checkSinglePath(graph.getPath(1, 7), "1 2 4 5 7 ");

    dijkstra(5, graph);
    //checkSinglePath(myGraph.getPath(5, 6), "5 7 6 ");

    dijkstra(7, graph);
    //checkSinglePath(graph.getPath(7, 1), "7 6 4 3 1 ");
}
