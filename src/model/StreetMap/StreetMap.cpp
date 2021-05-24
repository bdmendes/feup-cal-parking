#include <iostream>
#include <unistd.h>
#include "StreetMap.h"

StreetMap::StreetMap(unsigned int windowWidth, unsigned int windowHeight) :
        _gv(), _width(windowWidth), _height(windowHeight) {
}

void StreetMap::showGraph() {
    _gv.setCenter(sf::Vector2<float>(_width/2,_height/2));
    _gv.createWindow(_width, _height);
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
    retrieveDimensionLimits(nodesXY);
    nodesXY.seekg(0);
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
            colorNode(nodeId, sf::Color::Blue);
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
        addEdge(edgeId++, o, d, o->getElement().euclideanDistance(d->getElement()));
    }
}

Node<MapPoint> *StreetMap::addNode(id_t id, const MapPoint &element) {
    double x = _width * ((element.getX() - _minX) / (_maxX - _minX));
    double y = _height * ((element.getY() - _minY) / (_maxY - _minY));
    auto& gvNode = _gv.addNode(id, sf::Vector2f(x, y));
    _gvNodes[id] = &gvNode;
    return Graph::addNode(id, element);
}

Edge<MapPoint> *StreetMap::addEdge(id_t id, Node<MapPoint> *source, Node<MapPoint> *target, double weight) {
    auto& gvEdge = _gv.addEdge(id, _gv.getNode(source->getId()), _gv.getNode(target->getId()));
    _gvEdges[id] = &gvEdge;
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
            _gvNodes.erase((*it)->getId());
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
                _gvEdges.erase(it->getId());
                return;
            }
        }
    }
    throw std::logic_error("Edge does not exist");
}

void StreetMap::colorNode(id_t id, sf::Color color) {
    _gv.lock();
    _gvNodes.at(id)->setColor(color);
    _gv.unlock();
}

void StreetMap::colorEdge(id_t id, sf::Color color) {
    _gv.lock();
    _gvEdges.at(id)->setColor(color);
    _gv.unlock();
}

void StreetMap::resetEdgeColors() {
    _gv.lock();
    for (auto& edge : _gvEdges){
        edge.second->setColor();
    }
    _gv.unlock();
}

void StreetMap::resetNodeColors() {
    _gv.lock();
    for (auto& node : _gvNodes){
        node.second->setColor(findNodeById(node.second->getId())->getElement().isPark()
            ? sf::Color::Blue : sf::Color::Red);
    }
    _gv.unlock();
}

void StreetMap::retrieveDimensionLimits(std::ifstream &nodesXY) {
    double minX = INT32_MAX, minY = INT32_MAX, maxX = INT32_MIN, maxY = INT32_MIN;

    size_t numberOfNodes;
    nodesXY >> numberOfNodes;
    char sep;
    id_t nodeId;

    for (size_t i = 0; i < numberOfNodes; ++i){
        double x = 0, y = 0;
        nodesXY >> sep >> nodeId >> sep >> x >> sep >> y >> sep;
        if (x < minX){
            minX = x;
        } else if (x > maxX){
            maxX = x;
        }
        if (y < minY){
            minY = y;
        } else if (y > maxY){
            maxY = y;
        }
    }

    _minX = minX;
    _minY = minY;
    _maxX = maxX;
    _maxY = maxY;
}
