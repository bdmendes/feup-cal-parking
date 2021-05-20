#ifndef FEUP_CAL_PARKING_DIJKSTRA_H
#define FEUP_CAL_PARKING_DIJKSTRA_H

#include <limits>

#include "../../../lib/MutablePriorityQueue.h"
#include "../model/Graph/Graph.h"
#include "../model/Graph/Node.h"
#include "../model/Graph/Edge.h"

#define INF std::numeric_limits<double>::max()

template<class T>
void dijkstra(const T &origin,  const Graph<T> &graph) {
    for (auto& node : graph.getNodes()){
        node->dist = INF;
        node->path = nullptr;
    }

    auto startNode = findNode(origin);
    if (startNode == NULL) return;

    MutablePriorityQueue<Node<T>> q;
    startNode->dist = 0;
    q.insert(startNode);

    while (!q.empty()){
        auto currNode = q.extractMin();
        for (auto& e: currNode->getAdjacent()){
            auto destNode = e->getTarget();
            if (destNode->dist > currNode->dist + e->getWeight()){
                bool alreadyQueued = destNode->dist != INF;
                destNode->dist = currNode->dist + e.weight;
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

#endif //FEUP_CAL_PARKING_DIJKSTRA_H
