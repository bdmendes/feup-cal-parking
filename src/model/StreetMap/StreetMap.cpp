#include "StreetMap.h"

StreetMap::StreetMap(std::ifstream &nodesXY, std::ifstream &nodesLatLng, std::ifstream &edges) {
    size_t numberOfNodes{};
    nodesXY >> numberOfNodes;
    nodesLatLng >> numberOfNodes;

    size_t id{};
    double x{}, y{}, lat{}, lon{};
    char sep{};

    for (size_t i = 0; i < numberOfNodes; ++i) {
        nodesXY >> sep >> id >> sep >> x >> sep >> y >> sep;
        nodesLatLng >> sep >> id >> sep >> lat >> sep >> lon >> sep;
        int random = 1 + std::rand() / ((RAND_MAX + 1u) / 20);
        bool parking = random == 15;
        MapPoint point(x, y, lat, lon, parking);
        if (getNodes().empty()) {
            _minCoords = std::make_pair(point.getX(), point.getY());
            _maxCoords = std::make_pair(point.getX(), point.getY());
        } else {
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
        }

        addNode(id, point);
    }

    size_t numberOfEdges{};
    edges >> numberOfEdges;
    size_t originId{}, destinationId{};

    for (size_t i = 0; i < numberOfEdges; ++i) {
        edges >> sep >> originId >> sep >> destinationId >> sep;
        Node<MapPoint> *o = findNodeById(originId);
        Node<MapPoint> *d = findNodeById(destinationId);
        addEdge(o, d, 0.0);
    }
}

const std::pair<double, double> &StreetMap::getMinCoords() const {
    return _minCoords;
}

const std::pair<double, double> &StreetMap::getMaxCoords() const {
    return _maxCoords;
}
