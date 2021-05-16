#include "GraphviewerGUI.h"

#include <utility>
#include <iostream>


GraphviewerGUI::GraphviewerGUI(StreetMap map, double width, double height) : _map(std::move(map)),
                                                                             _width(width),
                                                                             _height(height) {}

void GraphviewerGUI::showGraph() {
    _gv = new GraphViewer();
    _gv->createWindow(_width, _height);
    for (auto node : _map.getNodes()) {
        double x = _width * ((node->getElement().getX() - _map.getMinCoords().first) /
                             (_map.getMaxCoords().first - _map.getMinCoords().first) * 0.9);
        double y = _height * ((node->getElement().getY() - _map.getMinCoords().second) /
                              (_map.getMaxCoords().second - _map.getMinCoords().second) * 0.9);
        _gv->addNode(node->getId(), sf::Vector2f(x, y));

    }
    size_t id = 1;
    for (auto node : _map.getNodes()) {
        for (auto edge : node->getAdjacent()) {
            _gv->addEdge(id, _gv->getNode(node->getId()), _gv->getNode(edge->getTarget()->getId()));
            id++;
        }
    }
    std::cout << "Finished drawing\n";
    _gv->join();
    delete _gv;
}

