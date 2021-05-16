#include <iostream>
#include <fstream>

#include "model/Graph/Graph.h"
#include "model/StreetMap/StreetMap.h"
#include "view/GraphviewerGUI.h"

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
    std::cout << "min coords " << map.getMinCoords().first << ", " << map.getMinCoords().second
              << "\n";
    std::cout << "max coords " << map.getMaxCoords().first << ", " << map.getMaxCoords().second
              << "\n";
    /*GraphviewerGUI gui(map, 200, 200);
    gui.createGraphviewer();
    gui.closeGraphViewer();*/
}
