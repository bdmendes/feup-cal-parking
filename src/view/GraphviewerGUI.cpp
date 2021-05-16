#include "GraphviewerGUI.h"


GraphviewerGUI::GraphviewerGUI(const StreetMap &map, double width, double height) : _map(map),
                                                                                    _width(width),
                                                                                    _height(height) {}

void GraphviewerGUI::createGV() {
    _gv = new GraphViewer();
    _gv->createWindow(_width, _height);
}

void GraphviewerGUI::deleteGV() {
    delete _gv;
}

void GraphviewerGUI::show() {
    createGV();
    for (Node<MapPoint> *node : _map.getNodes()) {
        _gv->addNode(node->getId(), sf::Vector2f())
    }
    deleteGV();
}


