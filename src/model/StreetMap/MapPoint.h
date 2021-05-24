#ifndef FEUP_CAL_PARKING_MAPPOINT_H
#define FEUP_CAL_PARKING_MAPPOINT_H

class MapPoint {
public:
    MapPoint(double x, double y, double latitude, double longitude, bool parking);

    MapPoint(double x, double y, bool parking = false);

    double getX() const;

    double getY() const;

    bool isParking() const;

    double euclideanDistance(const MapPoint& rhs) const;

    bool operator==(const MapPoint &rhs) const;

    bool operator!=(const MapPoint &rhs) const;

private:
    double _x;
    double _y;
    double _latitude;
    double _longitude;
    bool _parking;
};


#endif //FEUP_CAL_PARKING_MAPPOINT_H
