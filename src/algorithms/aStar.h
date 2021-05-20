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
        node->setDist(INF);
        node->setPath(nullptr);
    }

    auto startNode = graph.findNode(origin);
    if (startNode == NULL) return;

    MutablePriorityQueue<Node<T>> q;
    startNode->setDist(0);
    q.insert(startNode);

    while (!q.empty()){
        auto currNode = q.extractMin();
        for (auto& e: currNode->getAdjacent()){
            auto nextNode = e->getTarget();
            if (nextNode->getDist() > currNode->getDist() + e->getWeight()){
                bool alreadyQueued = nextNode->getDist() != INF;
                nextNode->setDist(currNode->getDist() + e->getWeight()) + calculateEuclideanDistance(nextNode, destiny);
                nextNode->setPath(currNode);
                if (alreadyQueued){
                    q.decreaseKey(nextNode);
                } else {
                    q.insert(nextNode);
                }
            }
        }
    }
}

#endif //FEUP_CAL_PARKING_ASTAR_H