#ifndef FEUP_CAL_PARKING_STREETMAP_H
#define FEUP_CAL_PARKING_STREETMAP_H

#include "../Graph/Graph.h"
#include "../MapPoint/MapPoint.h"
#include "graphviewer.h"
#include <fstream>

class StreetMap : public Graph<MapPoint> {
public:
    StreetMap(std::ifstream &nodesXY, std::ifstream &nodesLatLng, std::ifstream &edges, unsigned int width,
              unsigned int height);
    void showGraph();
private:
    GraphViewer _gv;
    unsigned _width;
    unsigned _height;
};


#endif //FEUP_CAL_PARKING_STREETMAP_H
