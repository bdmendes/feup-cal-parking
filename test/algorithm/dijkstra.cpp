#include <gtest/gtest.h>
#include "../../src/model/Graph/Graph.h"
#include "../../src/model/Graph/Node.h"
#include "../../src/algorithms/dijkstra.h"

Graph<int> createTestGraph() {
    Graph<int> myGraph;

    for(int i = 1; i <= 7; i++)
        myGraph.addNode(i, i);

    myGraph.addEdge(0, myGraph.getNodes().at(0), myGraph.getNodes().at(1), 2);
    myGraph.addEdge(1, myGraph.getNodes().at(0), myGraph.getNodes().at(3), 7);
    myGraph.addEdge(2, myGraph.getNodes().at(1), myGraph.getNodes().at(3), 3);
    myGraph.addEdge(3, myGraph.getNodes().at(1), myGraph.getNodes().at(4), 5);
    myGraph.addEdge(4, myGraph.getNodes().at(2), myGraph.getNodes().at(0), 2);
    myGraph.addEdge(5, myGraph.getNodes().at(2), myGraph.getNodes().at(5), 5);
    myGraph.addEdge(6, myGraph.getNodes().at(3), myGraph.getNodes().at(2), 1);
    myGraph.addEdge(7, myGraph.getNodes().at(3), myGraph.getNodes().at(4), 1);
    myGraph.addEdge(8, myGraph.getNodes().at(3), myGraph.getNodes().at(5), 6);
    myGraph.addEdge(9, myGraph.getNodes().at(3), myGraph.getNodes().at(6), 4);
    myGraph.addEdge(10, myGraph.getNodes().at(4), myGraph.getNodes().at(6), 2);
    myGraph.addEdge(11, myGraph.getNodes().at(5), myGraph.getNodes().at(3), 3);
    myGraph.addEdge(12, myGraph.getNodes().at(6), myGraph.getNodes().at(5), 4);

    return myGraph;
}

template<class T>
std::vector<T> getPath(const Graph<T>& graph, const T &origin, const T &dest) {
    std::vector<T> res;
    auto currNode = graph.findNode(dest);
    if (currNode == nullptr) return {};
    while (currNode != nullptr){
        res.push_back(currNode->getElement());
        currNode = currNode->getPath();
    }
    std::reverse(res.begin(), res.end());
    return res;
}

template <class T>
void checkAllPaths(Graph<T> &g, std::string expected) {
    std::stringstream ss;
    std::vector<Node<T>* > vs = g.getNodes();
    for(unsigned int i = 0; i < vs.size(); i++) {
        ss << vs[i]->getElement() << "<-";
        if ( vs[i]->getPath() != NULL )
            ss << vs[i]->getPath()->getElement();
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
    checkSinglePath(getPath(graph, 1, 7), "1 2 4 5 7 ");

    dijkstra(5, graph);
    checkSinglePath(getPath(graph, 5, 6), "5 7 6 ");

    dijkstra(7, graph);
    checkSinglePath(getPath(graph, 7, 1), "7 6 4 3 1 ");
}
