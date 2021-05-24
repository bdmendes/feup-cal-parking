#include "connectivity.h"

bool isStronglyConnected(const StreetMap &map) {
    return kosaraju(map);
}

static bool pointsAreAccessible(const std::vector<Node<MapPoint>*> &stopPoints, const StreetMap &map){
    for(unsigned int i = 0; i < stopPoints.size(); ++i){
        auto res = dfsFromNode(stopPoints.at(i), stopPoints, map);
        if(res.size() != stopPoints.size()) return false;
    }
    return true;
}

static bool existsPath(Node<MapPoint> *source, const std::vector<Node<MapPoint>*> &stopPoints, StreetMap &map) {
    std::vector<Node<MapPoint> *> res = dfsFromNode(source, stopPoints, map);
    return res.size() == stopPoints.size();
}

bool isConnected(StreetMap &map, const std::vector<Node<MapPoint>*> &stopPoints, Node<MapPoint> *source){
    return pointsAreAccessible(stopPoints, map) && existsPath(source, stopPoints, map);
}
