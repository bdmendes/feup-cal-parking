#include <iostream>

#include "model/Graph/Graph.h"
#include "algorithms/search.h"

template<class T>
void describeGraph(Graph<T> &g) {
    std::cout << "START DESCRIBING\n";
    for (auto n: g.getNodes()) {
        std::cout << n->getElement() << ", adjacent with: ";
        for (auto nn: n->getAdjacent()) {
            std::cout << nn->getTarget()->getElement() << "(w" << nn->getWeight() << ") ";
        }
        std::cout << "\n";
    }
    std::cout << "END DESCRIBING\n\n";
}

int main() {
    Graph<int> g;
    g.addNode(1);
    g.addNode(2);
    g.addNode(3);
    g.addNode(4);
    g.addEdge(4,2,3);
    describeGraph(g);
    g.removeEdge(4, 2);
    describeGraph(g);

    g.addEdge(1, 2, 0.0);
    g.addEdge(2, 3, 0.0);
    g.addEdge(1, 4, 0.0);

    std::vector<Node<int> *> targets{};

    targets.push_back(g.getNodes().at(2));
    targets.push_back(g.getNodes().at(1));

    std::vector<Node<int> *> res = bfs(g.getNodes().at(0), targets, g);

    describeGraph(g);
    g.removeNode(4);
    describeGraph(g);
}
