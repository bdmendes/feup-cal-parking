#ifndef FEUP_CAL_PARKING_CONNECTIVITY_HPP
#define FEUP_CAL_PARKING_CONNECTIVITY_HPP

#include "../algorithms/search.hpp"
#include "../model/StreetMap/StreetMap.h"

bool isStronglyConnected(const StreetMap &map) {
    return kosaraju(map);
}

bool isConnected(const std::vector<Node<MapPoint>*> &stopPoints, const StreetMap &map){
    std::vector<Node<MapPoint> *> res = dfsAll(stopPoints, map);
    return res.size() == stopPoints.size();
}

void calculateConnectivity(StreetMap &map, const std::vector<Node<MapPoint>*> &stopPoints){
    return isStronglyConnected(map) || isConnected(stopPoints, map);
}

#endif //FEUP_CAL_PARKING_CONNECTIVITY_HPP
