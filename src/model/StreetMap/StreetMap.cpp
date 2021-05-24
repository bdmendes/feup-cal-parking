#include <iostream>
#include "StreetMap.h"

#define COORDS_MAX_X 9500
#define COORDS_MIN_X -3300
#define COORDS_MAX_Y 3100
#define COORDS_MIN_Y -3000

StreetMap::StreetMap(unsigned int windowWidth, unsigned int windowHeight) :
        _gv(), _width(windowWidth), _height(windowHeight) {
}

void StreetMap::showGraph() {
    _gv.createWindow(_width, _height);
    _gv.setEnabledNodes(false);
    _gv.join();
}

void StreetMap::readFromFile(const std::string& nodesXYPath,
                             const std::string& nodesLatLongPath, const std::string& edgesPath){
    std::ifstream nodesXY(nodesXYPath);
    std::ifstream nodesLatLng(nodesLatLongPath);
    std::ifstream edges(edgesPath);
    if (!nodesXY || !nodesLatLng || !edges){
        throw std::invalid_argument("Invalid paths, check your working directory");
    }

    readNodes(nodesXY, nodesLatLng);
    readEdges(edges);
}

void StreetMap::readNodes(std::ifstream &nodesXY, std::ifstream &nodesLatLng) {
    size_t numberOfNodes;
    nodesXY >> numberOfNodes;
    nodesLatLng >> numberOfNodes;

    reserveNumberNodes(getNumberOfNodes());

    id_t nodeId;
    double x, y, lat, lon;
    char sep;
    for (size_t i = 0; i < numberOfNodes; ++i) {
        nodesXY >> sep >> nodeId >> sep >> x >> sep >> y >> sep;
        nodesLatLng >> sep >> nodeId >> sep >> lat >> sep >> lon >> sep;
        bool isPark = std::rand() % 20 == 0;
        if (isPark){
            unsigned capacity = 20 + std::rand() % 60;
            unsigned freeSpots = capacity / (2 + std::rand() % 3);
            double fixedTax = 3 + std::rand() % 7;
            double dynamicTax = fixedTax * (0.1*(2 + std::rand() % 3));
            ParkFields parkFields = {capacity, freeSpots, fixedTax, dynamicTax};
            MapPoint point(x, y, lat, lon, true, parkFields);
            addNode(nodeId, point);
        } else {
            MapPoint point(x, y, lat, lon);
            addNode(nodeId, point);
        }
    }
}

void StreetMap::readEdges(std::ifstream &edges) {
    id_t edgeId = 1, originId, destinationId;
    char sep;
    size_t numberOfEdges;
    edges >> numberOfEdges;
    for (size_t i = 0; i < numberOfEdges; ++i) {
        edges >> sep >> originId >> sep >> destinationId >> sep;
        Node<MapPoint> *o = findNodeById(originId);
        Node<MapPoint> *d = findNodeById(destinationId);
        addEdge(edgeId++, o, d, 1.0);
    }
}

Node<MapPoint> *StreetMap::addNode(id_t id, const MapPoint &element) {
    double x = (double) _width * ((element.getX() - COORDS_MIN_X) /
                                  (COORDS_MAX_X - COORDS_MIN_X) * 0.9);
    double y = (double) _height * ((element.getY() - COORDS_MIN_Y) /
                                   (COORDS_MAX_Y - COORDS_MIN_Y) * 0.9);
    _gv.addNode(id, sf::Vector2f(x, y));
    return Graph::addNode(id, element);
}

Edge<MapPoint> *StreetMap::addEdge(id_t id, Node<MapPoint> *source, Node<MapPoint> *target, double weight) {
    _gv.addEdge(id, _gv.getNode(source->getId()), _gv.getNode(target->getId()));
    return Graph::addEdge(id, source, target, weight);
}

void StreetMap::removeNode(const MapPoint &element) {
    auto node = findNode(element);
    if (node == nullptr) {
        throw std::logic_error("Node does not exist");
    }
    for (auto it = _nodes.begin(); it != _nodes.end(); it++) {
        if (*it == node) {
            _nodes.erase(it);
            _gv.removeNode((*it)->getId());
            return;
        }
    }
    throw std::logic_error("Node does not exist");
}

void StreetMap::removeEdge(const MapPoint &source, const MapPoint &target) {
    for (auto &n : _nodes) {
        if (n->getElement() != source) continue;
        auto adj = n->getAdjacent();
        for (auto& it : adj) {
            if (it->getTarget()->getElement() == target) {
                n->removeEdge(it->getTarget());
                _gv.removeEdge(it->getId());
                return;
            }
        }
    }
    throw std::logic_error("Edge does not exist");
}
