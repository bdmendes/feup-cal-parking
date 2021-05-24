#ifndef FEUP_CAL_PARKING_CONNECTIVITY_H
#define FEUP_CAL_PARKING_CONNECTIVITY_H

#include "../algorithms/search.hpp"
#include "../model/StreetMap/StreetMap.h"

bool isStronglyConnected(const StreetMap &map);
bool isConnected(StreetMap &map, const std::vector<Node<MapPoint>*> &stopPoints, Node<MapPoint> *source);


#endif //FEUP_CAL_PARKING_CONNECTIVITY_H
