#include "GraphviewerGUI.h"

#include <utility>
#include <iostream>


GraphviewerGUI::GraphviewerGUI(StreetMap map, double width, double height) : _map(std::move(map)),
                                                                             _width(width),
                                                                             _height(height) {}

void GraphviewerGUI::showGraph() {
    _gv = new GraphViewer();
    std::cout << "Created viewer\n";
    _gv->createWindow(_width, _height);
    std::cout << "Created window\n";
    for (const auto& node : _map.getNodes()) {
        double x = (double)_width * ((node->getElement().getX() - _map.getMinCoords().first) /
                             (_map.getMaxCoords().first - _map.getMinCoords().first) * 0.9);
        double y = (double)_height * ((node->getElement().getY() - _map.getMinCoords().second) /
                              (_map.getMaxCoords().second - _map.getMinCoords().second) * 0.9);
        auto n = _gv->addNode(node->getId(), sf::Vector2f(x, y));
        if (node->getElement().isParking()) {
            n.setColor(GraphViewer::CYAN);
        }
    }
    size_t id = 1;
    for (const auto& node : _map.getNodes()) {
        for (const auto& edge : node->getAdjacent()) {
            _gv->addEdge(id++, _gv->getNode(node->getId()), _gv->getNode(edge->getTarget()->getId()));
        }
    }
    std::cout << "Finished drawing\n";
    _gv->join();
    delete _gv;
}

