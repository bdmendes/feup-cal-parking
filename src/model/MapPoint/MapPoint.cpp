#include "MapPoint.h"

MapPoint::MapPoint(double x, double y, double latitude, double longitude)
        : _x(x), _y(y), _latitude(latitude), _longitude(longitude) {}

double MapPoint::getX() const {
    return _x;
}

double MapPoint::getY() const {
    return _y;
}
