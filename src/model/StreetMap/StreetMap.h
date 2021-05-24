#ifndef FEUP_CAL_PARKING_STREETMAP_H
#define FEUP_CAL_PARKING_STREETMAP_H

#include "../Graph/Graph.hpp"
#include "MapPoint.h"

#include "graphviewer.h"
#include <fstream>

class StreetMap : public Graph<MapPoint> {
public:
    StreetMap(unsigned int windowWidth, unsigned int windowHeight);
    void readFromFile(const std::string& nodesXYPath,
                      const std::string& nodesLatLongPath, const std::string& edgesPath);
    void showGraph();
    Node<MapPoint> * addNode(id_t id, const MapPoint &element) override;
    Edge<MapPoint> * addEdge(id_t id, Node<MapPoint> *source, Node<MapPoint> *target, double weight) override;
    void removeNode(const MapPoint &element) override;
    void removeEdge(const MapPoint &source, const MapPoint &target) override;
private:
    void readNodes(std::ifstream& nodesXY, std::ifstream& nodesLatLng);
    void readEdges(std::ifstream& edges);
    GraphViewer _gv;
    unsigned _width;
    unsigned _height;
};

#endif //FEUP_CAL_PARKING_STREETMAP_H
