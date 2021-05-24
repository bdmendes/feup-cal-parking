#ifndef FEUP_CAL_PARKING_PARKSELECTOR_H
#define FEUP_CAL_PARKING_PARKSELECTOR_H

#include <vector>
#include "../model/StreetMap/MapPoint.h"

std::vector<MapPoint*> getPathAfterParkReplacement(const MapPoint& source, const MapPoint& target,
                                 const std::vector<MapPoint*>& stopPoints, const std::vector<bool>& shallPark,
                                 std::vector<double>& parkDistance, std::vector<std::vector<MapPoint*>>& parkWalkPaths,
                                 int i, int j, int k, double maxDistance);

#endif //FEUP_CAL_PARKING_PARKSELECTOR_H
