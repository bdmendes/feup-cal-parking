#include "GraphviewerGUI.h"

#include <utility>
#include <iostream>


GraphviewerGUI::GraphviewerGUI(StreetMap map, double width, double height) : _map(std::move(map)),
                                                                             _width(width),
                                                                             _height(height) {}

void GraphviewerGUI::showGraph() {
    _gv = new GraphViewer();
    _gv->createWindow(_width, _height);
    _gv->setEnabledNodes(false);
    auto maxCoords = _map.getMaxCoords();
    auto minCoords = _map.getMinCoords();
    for (const auto &node : _map.getNodes()) {
        auto element = node->getElement();
        double x = (double) _width * ((element.getX() - minCoords.first) /
                                      (maxCoords.first - minCoords.first) * 0.9);
        double y = (double) _height * ((element.getY() - minCoords.second) /
                                       (maxCoords.second - minCoords.second) * 0.9);
        auto n = _gv->addNode(node->getId(), sf::Vector2f(x, y));
        if (node->getElement().isParking()) {
            n.setColor(GraphViewer::CYAN);
        }
    }
    id_t id = 1;
    for (const auto &node : _map.getNodes()) {
        for (const auto &edge : node->getAdjacent()) {
            _gv->addEdge(id++, _gv->getNode(node->getId()), _gv->getNode(edge->getTarget()->getId()));
        }
    }
    _gv->join();
    delete _gv;
}
