#include <iostream>

#include "model/Graph/Graph.h"
#include "ui/menu/menu.h"

template <class T>
void describeGraph(Graph<T>& g){
    std::cout << "START DESCRIBING\n";
    for (auto n: g.getNodes()){
        std::cout << n->getElement() << ", adjacent with: ";
        for (auto nn: n->getAdjacent()){
            std::cout << nn->getTarget()->getElement() << "(w" << nn->getWeight() << ") ";
        }
        std::cout << "\n";
    }
    std::cout << "END DESCRIBING\n\n";
}

int main() {
    /*Graph<int> g;
    g.addNode(2);
    g.addNode(4);
    g.addEdge(4,2,3);
    describeGraph(g);
    g.removeEdge(4, 2);
    describeGraph(g);
    describeGraph(g);
    g.removeNode(4);
    describeGraph(g);*/

    IntroMenu introMenu;

    introMenu.show();
}
