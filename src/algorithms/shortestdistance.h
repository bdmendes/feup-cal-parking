#ifndef FEUP_CAL_PARKING_SHORTESTDISTANCE_H
#define FEUP_CAL_PARKING_SHORTESTDISTANCE_H

#include <limits>
#include <algorithm>
#include <math.h>

#include "../model/StreetMap/StreetMap.h"
#include "../../../lib/MutablePriorityQueue.h"
#include "../model/Graph/Graph.h"

#define INF std::numeric_limits<double>::max()

template<class T>
void dijkstra(const T &origin, Graph<T> &graph) {
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
            auto destNode = e->getTarget();
            if (destNode->getDist() > currNode->getDist() + e->getWeight()){
                bool alreadyQueued = destNode->getDist() != INF;
                destNode->setDist(currNode->getDist() + e->getWeight());
                destNode->setPath(currNode);
                if (alreadyQueued){
                    q.decreaseKey(destNode);
                } else {
                    q.insert(destNode);
                }
            }
        }
    }
}

template<class T>
std::vector<Node<T>*> getPath(Graph<T>& graph, const T &origin, const T &dest){
    std::vector<Node<T>*> res;
    auto sourceNode = graph.findNode(origin);
    if (sourceNode == nullptr){
        throw std::logic_error("Source node not found");
    }
    auto currNode = graph.findNode(dest);
    if (currNode == nullptr){
        throw std::logic_error("Target node not found");
    }
    for(;;){
        res.push_back(currNode);
        if (currNode->getElement() == sourceNode->getElement()) break;
        currNode = currNode->getPath();
        if (currNode == nullptr) break;
    }
    std::reverse(res.begin(), res.end());
    if (res.at(0)->getElement() != sourceNode->getElement()){
        throw std::logic_error("Invalid path");
    }
    return res;
}

template<class T>
double distance(std::vector<Node<T>*> path){
    double total = 0;
    for (int i = 0; i < path.size() - 1; i++){
        bool foundNext = false;
        for (auto adj : path.at(i)->getAdjacent()){
            if (adj->getTarget() == path.at(i+1)){
                total += adj->getWeight();
                foundNext = true;
                break;
            }
        }
        if (!foundNext){
            throw std::logic_error("Path nodes are not connected");
        }
    }
    return total;
}

static double euclideanDistance(Node<MapPoint> &current, Node<MapPoint> &target){
    return sqrt(pow(current.getElement().getX() - target.getElement().getX(), 2)
        + pow(current.getElement().getY() - target.getElement().getY(), 2));
}

void AStar(const MapPoint &origin, StreetMap &graph, const MapPoint &target) {
    for (auto& node : graph.getNodes()){
        node->setDist(INF);
        node->setPath(nullptr);
    }

    auto startNode = graph.findNode(origin);
    if (startNode == NULL){
        throw std::logic_error("Source node does not exist");
    }
    auto endNode = graph.findNode(target);
    if (endNode == NULL){
        throw std::logic_error("Target node does not exist");
    }

    MutablePriorityQueue<Node<MapPoint>> q;
    startNode->setDist(0);
    q.insert(startNode);

    while (!q.empty()){
        auto currNode = q.extractMin();
        if (currNode->getElement() == target) break;
        for (auto& e: currNode->getAdjacent()){
            auto nextNode = e->getTarget();
            if (nextNode->getDist() > currNode->getDist() + e->getWeight()){
                bool alreadyQueued = nextNode->getDist() != INF;
                nextNode->setDist(currNode->getDist() + e->getWeight()
                    + euclideanDistance(*nextNode, *endNode));
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

#endif //FEUP_CAL_PARKING_SHORTESTDISTANCE_H
