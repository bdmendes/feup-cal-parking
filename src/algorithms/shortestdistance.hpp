#ifndef FEUP_CAL_PARKING_SHORTESTDISTANCE_HPP
#define FEUP_CAL_PARKING_SHORTESTDISTANCE_HPP

#include <limits>
#include <algorithm>
#include <math.h>

#include "../model/StreetMap/StreetMap.h"
#include "../../../lib/MutablePriorityQueue.h"
#include "../model/Graph/Graph.hpp"

#define INF std::numeric_limits<double>::max()

template<class T>
inline void dijkstra(const T &origin, Graph<T> &graph) {
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
inline std::vector<Node<T>*> getDijkstraPath(const Graph<T>& graph, const T &origin, const T &dest){
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
inline std::vector<Node<T>*> getAStarPath(const Graph<T>& graph, const T &origin, const T &dest){
    return getDijkstraPath(graph, origin, dest);
}

template<class T>
inline double distance(const std::vector<Node<T>*>& path){
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

inline void AStar(const MapPoint &origin, const Graph<MapPoint> &graph, const MapPoint &target) {
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
        for (auto& e: currNode->getAdjacent()){
            auto nextNode = e->getTarget();
            double heuristic = nextNode->getElement().euclideanDistance(endNode->getElement());
            double newDist = currNode->getDist() + e->getWeight() + heuristic;
            if (nextNode->getDist() > newDist){
                bool alreadyQueued = nextNode->getDist() != INF;
                nextNode->setDist(newDist);
                nextNode->setPath(currNode);
                if (nextNode->getElement() == target){
                    return;
                }
                else if (alreadyQueued){
                    q.decreaseKey(nextNode);
                } else {
                    q.insert(nextNode);
                }
            }
        }
    }
}

template <class T>
inline std::vector<std::vector<std::vector<Node<T>*>>> floydWarshall(const Graph<T>& graph) {
    auto distMatrix = graph.getAdjacencyMatrix();
    std::vector<std::vector<std::vector<Node<T>*>>>
            pathMatrix(distMatrix.size(), std::vector<std::vector<Node<T>*>>());
    for (auto& l : pathMatrix) {
        l.resize(distMatrix.size(), std::vector<Node<T>*>());
    }

    for (int k = 0; k < distMatrix.size(); k++){
        auto middleMan = graph.findNodeById(k);
        if (middleMan == nullptr) continue;
        for (int i = 0; i < distMatrix.size(); i++){
            for (int j = 0; j < distMatrix.size(); j++){
                if (distMatrix.at(i).at(k) + distMatrix.at(k).at(j) < distMatrix.at(i).at(j)){
                    distMatrix.at(i).at(j) = distMatrix.at(i).at(k) + distMatrix.at(k).at(j);
                    auto& fullPath = pathMatrix.at(i).at(j);
                    auto pathBeforeMiddleMan = pathMatrix.at(i).at(k);
                    auto pathAfterMiddleMan = pathMatrix.at(k).at(j);
                    fullPath = pathBeforeMiddleMan;
                    fullPath.push_back(middleMan);
                    fullPath.insert(fullPath.end(), pathAfterMiddleMan.begin(),
                                    pathAfterMiddleMan.end());
                }
            }
        }
    }

    return pathMatrix;
}

#endif //FEUP_CAL_PARKING_SHORTESTDISTANCE_HPP
