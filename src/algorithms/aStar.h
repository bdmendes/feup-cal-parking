#ifndef FEUP_CAL_PARKING_ASTAR_H
#define FEUP_CAL_PARKING_ASTAR_H

#include <cmath>
#include <limits>

#include "../model/StreetMap/StreetMap.h"
#include "../../../lib/MutablePriorityQueue.h"
#include "../model/Graph/Graph.h"
#include "../model/Graph/Node.h"
#include "../model/Graph/Edge.h"

#define INF std::numeric_limits<double>::max()


double calculateEuclideanDistance(Node<MapPoint> &current, Node<MapPoint> &destiny){
    return sqrt(pow(current.getElement().getX() - destiny.getElement().getX(), 2) + pow(current.getElement().getY() - destiny.getElement().getY(), 2));
}

void aStarWithEuclideanDistance(const MapPoint &origin, StreetMap &graph, const MapPoint &destiny) {
    for (auto& node : graph.getNodes()){
        node->dist = INF;
        node->path = nullptr;
    }

    auto startNode = findNode(origin);
    if (startNode == NULL) return;

    MutablePriorityQueue<Node<MapPoint>> q;
    startNode->dist = 0;
    q.insert(startNode);

    while (!q.empty()){
        auto currNode = q.extractMin();
        for (auto& e: currNode->getAdjacent()){
            auto destNode = e->getTarget();
            if (destNode->dist > currNode->dist + e->getWeight()){
                bool alreadyQueued = destNode->dist != INF;
                destNode->dist = currNode->dist + e.weight + calculateEuclideanDistance(destNode, destiny);
                destNode->path = currNode;
                if (alreadyQueued){
                    q.decreaseKey(destNode);
                } else {
                    q.insert(destNode);
                }
            }
        }
    }
}

#endif //FEUP_CAL_PARKING_ASTAR_H