#ifndef FEUP_CAL_PARKING_CONNECTIVITY_H
#define FEUP_CAL_PARKING_CONNECTIVITY_H

#include "../algorithms/search.hpp"
#include "../model/StreetMap/StreetMap.h"

bool isConnected(StreetMap &map, const std::vector<Node<MapPoint>*> &stopPoints);

#endif //FEUP_CAL_PARKING_CONNECTIVITY_H
