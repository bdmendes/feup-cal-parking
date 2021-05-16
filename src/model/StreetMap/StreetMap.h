#ifndef FEUP_CAL_PARKING_STREETMAP_H
#define FEUP_CAL_PARKING_STREETMAP_H

#include "../Graph/Graph.h"
#include "../MapPoint/MapPoint.h"
#include <fstream>

class StreetMap : public Graph<MapPoint> {
public:
    StreetMap(std::ifstream &nodesXY, std::ifstream &nodesLatLng, std::ifstream &edges);

    const std::pair<double, double> &getMinCoords() const;

    const std::pair<double, double> &getMaxCoords() const;

private:
    std::pair<double, double> _minCoords;
    std::pair<double, double> _maxCoords;
};


#endif //FEUP_CAL_PARKING_STREETMAP_H
