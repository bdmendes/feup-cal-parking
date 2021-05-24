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

static bool existsPath(Node<MapPoint> *source, const std::vector<Node<MapPoint>*> &stopPoints) {
    std::vector<Node<MapPoint> *> res;
    dfsVisit(source, stopPoints, res);
    return res.size() == stopPoints.size();
}

void calculateConectivity(StreetMap &map, const std::vector<Node<MapPoint>*> &stopPoints, Node<MapPoint> *source){
    if (isStronglyConnected(map)) std::cout << "The graph is strongly connected.\n";
    else if (isConnected(stopPoints, map)) std::cout << "The graph is connected.\n";
    else if (existsPath(source, stopPoints)) std::cout << "The graph isn't connected but there is a possible solution for the problem.\n";
    else std::cout << "Cannot calculate this route\n";
}