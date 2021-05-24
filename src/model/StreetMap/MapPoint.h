#ifndef FEUP_CAL_PARKING_MAPPOINT_H
#define FEUP_CAL_PARKING_MAPPOINT_H

typedef struct {
    unsigned capacity;
    unsigned freeSpots;
    double fixedPrice;
    double capacityTaxFactor;
} ParkFields;

class MapPoint {
public:
    MapPoint(double x, double y, double latitude, double longitude, bool park = false, ParkFields parkFields = {});

    MapPoint(double x, double y);

    double getLatitude() const;

    double getLongitude() const;

    bool isPark() const;

    const ParkFields &getParkFields() const;

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
    bool _park;
    ParkFields _parkFields;
};


#endif //FEUP_CAL_PARKING_MAPPOINT_H
