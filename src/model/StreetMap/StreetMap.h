#ifndef FEUP_CAL_PARKING_STREETMAP_H
#define FEUP_CAL_PARKING_STREETMAP_H

#include "../Graph/Graph.h"
#include "../MapPoint/MapPoint.h"
#include "graphviewer.h"

class StreetMap : public Graph<MapPoint> {
public:

    StreetMap(std::ifstream &nodesXY, std::ifstream &nodesLatLng, std::ifstream &edges);

private:
    static GraphViewer gv;
};

StreetMap::StreetMap(std::ifstream &nodesXY, std::ifstream &nodesLatLng, std::ifstream &edges) : Graph<MapPoint>() {

    size_t numberOfNodes{};
    nodesXY >> numberOfNodes;
    nodesLatLng >> numberOfNodes;

    size_t id{};
    double x{}, y{}, lat{}, lon{};
    char sep{};

    for (size_t i = 0; i < numberOfNodes; ++i) {
        nodesXY >> sep >> id >> sep >> x >> sep >> y >> sep;
        nodesLatLng >> sep >> id >> sep >> lat >> sep >> lon >> sep;
        MapPoint point(x, y, lat, lon);
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


#endif //FEUP_CAL_PARKING_STREETMAP_H
