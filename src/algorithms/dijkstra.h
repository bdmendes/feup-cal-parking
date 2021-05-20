#ifndef FEUP_CAL_PARKING_DIJKSTRA_H
#define FEUP_CAL_PARKING_DIJKSTRA_H

#include <limits>
#include <algorithm>

#include "../../../lib/MutablePriorityQueue.h"
#include "../model/Graph/Graph.h"
#include "../model/Graph/Node.h"
#include "../model/Graph/Edge.h"

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
std::vector<T> getPath(const T &origin, const T &dest){
    std::vector<T> res;
    auto currNode = findNode(dest);
    if (currNode == nullptr) return {};
    while (currNode != nullptr){
        res.push_back(currNode->getElement());
        currNode = currNode->getPath();
    }
    std::reverse(res.begin(), res.end());
    return res;
}

#endif //FEUP_CAL_PARKING_DIJKSTRA_H
