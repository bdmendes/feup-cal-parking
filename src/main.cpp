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

    g.addEdge(1, 2, 0.0);
    g.addEdge(2, 3, 0.0);
    g.addEdge(1, 4, 0.0);

    std::vector<Node<int> *> targets{};

    auto *n1 = new Node<int>(1);
    auto *n2 = new Node<int>(2);

    targets.push_back(n1);
    targets.push_back(n2);

    std::vector<Node<int> *> res = dfs(targets, g);

    describeGraph(g);
}
