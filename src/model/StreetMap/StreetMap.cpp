#include <iostream>
#include <climits>
#include "StreetMap.h"

#define COORDS_MAX_X 9500
#define COORDS_MIN_X -3300
#define COORDS_MAX_Y 3100
#define COORDS_MIN_Y -3000

StreetMap::StreetMap(std::ifstream &nodesXY, std::ifstream &nodesLatLng, std::ifstream &edges, unsigned int width,
                     unsigned int height) : _gv(), _width(width), _height(height) {

    size_t numberOfNodes{};
    nodesXY >> numberOfNodes;
    nodesLatLng >> numberOfNodes;

    id_t nodeId{};
    double x{}, y{}, lat{}, lon{};
    char sep{};

    reserveNumberNodes(getNumberOfNodes());
    for (size_t i = 0; i < numberOfNodes; ++i) {
        nodesXY >> sep >> nodeId >> sep >> x >> sep >> y >> sep;
        nodesLatLng >> sep >> nodeId >> sep >> lat >> sep >> lon >> sep;
        MapPoint point(x, y, lat, lon, std::rand() % 20 == 0);
        double x = (double) _width * ((point.getX() - COORDS_MIN_X) /
                                      (COORDS_MAX_X - COORDS_MIN_X) * 0.9);
        double y = (double) _height * ((point.getY() - COORDS_MIN_Y) /
                                       (COORDS_MAX_Y - COORDS_MIN_Y) * 0.9);
        auto n = _gv.addNode(nodeId, sf::Vector2f(x, y));
        if (point.isParking()) {
            n.setColor(GraphViewer::CYAN);
        }
        addNode(nodeId, point);
    }

    id_t edgeId{};

    size_t numberOfEdges{};
    edges >> numberOfEdges;
    id_t originId{}, destinationId{};

    for (size_t i = 0; i < numberOfEdges; ++i) {
        edges >> sep >> originId >> sep >> destinationId >> sep;
        Node<MapPoint> *o = findNodeById(originId);
        Node<MapPoint> *d = findNodeById(destinationId);
        addEdge(edgeId, o, d, 1.0);
        _gv.addEdge(edgeId++, _gv.getNode(originId), _gv.getNode(destinationId));
    }
}

void StreetMap::showGraph() {
    _gv.createWindow(_width, _height);
    _gv.setEnabledNodes(false);
    _gv.join();
}

