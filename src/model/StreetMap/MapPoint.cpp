#include "MapPoint.h"
#include <math.h>

MapPoint::MapPoint(double x, double y, double latitude, double longitude, bool parking)
        : _x(x), _y(y), _latitude(latitude), _longitude(longitude), _parking(parking) {}

double MapPoint::getX() const {
    return _x;
}

double MapPoint::getY() const {
    return _y;
}

bool MapPoint::isParking() const {
    return _parking;
}

bool MapPoint::operator==(const MapPoint &rhs) const {
    return _x == rhs._x &&
           _y == rhs._y;
}

bool MapPoint::operator!=(const MapPoint &rhs) const {
    return !(rhs == *this);
}

MapPoint::MapPoint(double x, double y, bool parking) :
    _x(x), _y(y), _parking(parking){

}

double MapPoint::euclideanDistance(const MapPoint &rhs) const {
    return sqrt(pow(getX() - rhs.getX(), 2) + pow(getY() - rhs.getY(), 2));
}
