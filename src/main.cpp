#include <iostream>
#include <fstream>

#include "model/Graph/Graph.hpp"
#include "model/StreetMap/StreetMap.h"
#include "algorithms/search.hpp"
#include "controller/parkselector.h"

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
    std::string nodesXY("maps/porto/porto_strong_nodes_xy.txt");
    std::string nodesLL("maps/porto/porto_strong_nodes_latlng.txt");
    std::string edges("maps/porto/porto_strong_edges.txt");
    StreetMap map(1900, 1000);
    map.readFromFile(nodesXY, nodesLL, edges);
    map.showGraph();
}
