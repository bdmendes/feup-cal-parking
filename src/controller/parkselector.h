#ifndef FEUP_CAL_PARKING_PARKSELECTOR_H
#define FEUP_CAL_PARKING_PARKSELECTOR_H

#include <vector>
#include "../model/StreetMap/MapPoint.h"
#include "../model/Graph/Graph.hpp"

std::vector<Node<MapPoint>*>
getPathAfterParkReplacement(const Graph<MapPoint>& graph, const std::vector<Node<MapPoint>*>& stopPoints, Node<MapPoint>* endNode,
                            const std::vector<bool>& shallPark, int iFactor, int jFactor, int kFactor, double maxDistance);

#endif //FEUP_CAL_PARKING_PARKSELECTOR_H
