#ifndef FEUP_CAL_PARKING_MAPPOINT_H
#define FEUP_CAL_PARKING_MAPPOINT_H

#include "../Graph/Node.h"


class MapPoint {
public:
    MapPoint(double x, double y, double latitude, double longitude);

private:
    double _x;
    double _y;
    double _latitude;
    double _longitude;
    bool _isParking;
};


#endif //FEUP_CAL_PARKING_MAPPOINT_H
