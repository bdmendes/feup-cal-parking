#include "connectivity.h"

static bool isStronglyConnected(const StreetMap &map) {
    return kosaraju(map);
}

static bool isConnected(const std::vector<Node<MapPoint>*> &stopPoints, const StreetMap &map){
    for(unsigned int i = 0; i < stopPoints.size(); ++i){
        auto res = dfsFromNode(stopPoints.at(i), stopPoints, map);
        if(res.size() != stopPoints.size()) return false;
    }
    return true;
}

bool calculateConectivity(StreetMap &map, const std::vector<Node<MapPoint>*> &stopPoints){
    return isStronglyConnected(map) || isConnected(stopPoints, map);
}