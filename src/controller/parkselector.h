#ifndef FEUP_CAL_PARKING_PARKSELECTOR_H
#define FEUP_CAL_PARKING_PARKSELECTOR_H

#include <vector>
#include "../model/StreetMap/MapPoint.h"
#include "../model/Graph/Graph.hpp"

std::vector<Node<MapPoint>*>
getPathAfterParkReplacement(Graph<MapPoint>& graph, const std::vector<Node<MapPoint>*>& stopPoints, Node<MapPoint>* sourceNode, Node<MapPoint>* endNode,
                            std::vector<bool> shallPark, float iFactor, float jFactor, float kFactor, double maxEuclideanDistance);

std::vector<std::vector<Node<MapPoint>*>> getWalkPaths(Graph<MapPoint>& graph, const std::vector<Node<MapPoint>*>& stopPoints,
                                                       const std::vector<Node<MapPoint>*>& actualStops);

#endif //FEUP_CAL_PARKING_PARKSELECTOR_H
