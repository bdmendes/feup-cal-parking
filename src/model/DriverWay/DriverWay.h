#ifndef FEUP_CAL_PARKING_DRIVERWAY_H
#define FEUP_CAL_PARKING_DRIVERWAY_H

#include "../StreetMap/StreetMap.h"
#include "../MapPoint/Park.h"


class DriverWay : protected StreetMap {
public:
    DriverWay(MapPoint* source, MapPoint* target);
    void addStopPoint(MapPoint* point, Park* park);
    void removeStopPoint(MapPoint* point);
    void addPath(MapPoint* p1, MapPoint* p2, double distance);
    MapPoint* getSource();
    MapPoint* getTarget();
    std::vector<std::pair<MapPoint*,Park*>> getStopPoints();
private:
    std::vector<std::pair<MapPoint*,Park*>> _stopPoints;
    MapPoint* source, target;
};


#endif //FEUP_CAL_PARKING_DRIVERWAY_H
