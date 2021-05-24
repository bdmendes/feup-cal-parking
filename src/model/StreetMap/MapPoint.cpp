#include <stdexcept>
#include "MapPoint.h"

MapPoint::MapPoint(double x, double y, double latitude, double longitude, bool park, ParkFields parkFields)
        : _x(x), _y(y), _latitude(latitude), _longitude(longitude), _park(park), _parkFields(parkFields) {

}

double MapPoint::getX() const {
    return _x;
}

double MapPoint::getY() const {
    return _y;
}

bool MapPoint::operator==(const MapPoint &rhs) const {
    return _x == rhs._x &&
           _y == rhs._y;
}

bool MapPoint::operator!=(const MapPoint &rhs) const {
    return !(rhs == *this);
}

MapPoint::MapPoint(double x, double y) :
    _x(x), _y(y), _latitude(0), _longitude(0), _park(false), _parkFields(){

}

double MapPoint::getLatitude() const {
    return _latitude;
}

double MapPoint::getLongitude() const {
    return _longitude;
}

bool MapPoint::isPark() const {
    return _park;
}

const ParkFields &MapPoint::getParkFields() const {
    if (!isPark()){
        throw std::logic_error("This map point is not a park");
    }
    return _parkFields;
}
