#include <iostream>
#include <climits>
#include "StreetMap.h"

StreetMap::StreetMap(std::ifstream &nodesXY, std::ifstream &nodesLatLng, std::ifstream &edges):
    _maxCoords(std::make_pair(LONG_MIN, LONG_MIN)), _minCoords(std::make_pair(LONG_MAX, LONG_MAX)){
    size_t numberOfNodes{};
    nodesXY >> numberOfNodes;
    nodesLatLng >> numberOfNodes;

    size_t id{};
    double x{}, y{}, lat{}, lon{};
    char sep{};

    reserveNumberNodes(getNumberOfNodes());
    for (size_t i = 0; i < numberOfNodes; ++i) {
        std::cout << "node " << i << "\n";
        nodesXY >> sep >> id >> sep >> x >> sep >> y >> sep;
        nodesLatLng >> sep >> id >> sep >> lat >> sep >> lon >> sep;
        MapPoint point(x, y, lat, lon, std::rand() % 20 == 0);
        if (point.getX() > _maxCoords.first) {
            _maxCoords.first = point.getX();
        }
        if (point.getX() < _minCoords.first) {
            _minCoords.first = point.getX();
        }
        if (point.getY() > _maxCoords.second) {
            _maxCoords.second = point.getY();
        }
        if (point.getY() < _minCoords.second) {
            _minCoords.second = point.getY();
        }
        addNode(id, point);
    }

    size_t numberOfEdges{};
    edges >> numberOfEdges;
    size_t originId{}, destinationId{};

    for (size_t i = 0; i < numberOfEdges; ++i) {
        std::cout << "edge " << i << "\n";
        edges >> sep >> originId >> sep >> destinationId >> sep;
        Node<MapPoint> *o = findNodeById(originId);
        Node<MapPoint> *d = findNodeById(destinationId);
        addEdge(o, d, 0.0);
    }
}

std::pair<double, double> StreetMap::getMinCoords() const {
    return _minCoords;
}

std::pair<double, double> StreetMap::getMaxCoords() const {
    return _maxCoords;
}
