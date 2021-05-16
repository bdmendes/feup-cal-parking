#ifndef FEUP_CAL_PARKING_MAPPOINT_H
#define FEUP_CAL_PARKING_MAPPOINT_H

class MapPoint {
public:
    MapPoint(double x, double y, double latitude, double longitude, bool parking);

    double getX() const;

    double getY() const;

    bool isParking() const;

private:
    double _x;
    double _y;
    double _latitude;
    double _longitude;
    bool _parking;
};


#endif //FEUP_CAL_PARKING_MAPPOINT_H
