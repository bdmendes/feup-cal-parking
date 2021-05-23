#include <iostream>
#include <fstream>

#include "model/Graph/Graph.hpp"
#include "ui/menu/menu.h"
#include "model/StreetMap/StreetMap.h"
#include "algorithms/search.hpp"


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

    std::srand(std::time(nullptr));

    StreetMap map(1900, 1000);

    IntroMenu introMenu(map);
    introMenu.show();

    map.showGraph();
}
