#include <iostream>
#include <fstream>

#include "model/Graph/Graph.h"
#include "algorithms/search.h"
#include "model/StreetMap/StreetMap.h"

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
    std::ifstream nodesXY("maps/porto/porto_full_nodes_xy.txt");
    std::ifstream nodesLL("maps/porto/porto_full_nodes_latlng.txt");
    std::ifstream edges("maps/porto/porto_full_edges.txt");
    StreetMap map(nodesXY, nodesLL, edges);
    std::cout << map.getNumberOfNodes() << "\n";
}
