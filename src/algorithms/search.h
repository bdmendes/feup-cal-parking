#ifndef FEUP_CAL_PARKING_SEARCH_H
#define FEUP_CAL_PARKING_SEARCH_H

#include "../model/Graph/Graph.h"
#include "algorithm"

template<class T>
std::vector<Node<T> *> dfs(const std::vector<Node<T> *> &targets, const Graph<T> &graph) {
    std::vector<Node<T> *> res{};
    for (Node<T> *node : graph.getNodes()) {
        node->setUnvisited();
    }
    for (Node<T> *node : graph.getNodes()) {
        if (res.size() == targets.size()) {
            break;
        }


        if (!node->isVisited()) {
            dfsVisit(node, graph, targets, res);
        }
    }
    return res;
}

template<class T>
void
dfsVisit(Node<T> *node, const std::vector<Node<T> *> &targets, std::vector<Node<T> *> &found) {
    node->setVisited();
    bool isTarget = std::find_if(targets.begin(), targets.end(), [&](Node<T> *n1) {
        return n1->getElement() == node->getElement();
    }) != targets.end();
    if (isTarget) {
        found.push_back(node);
    }
    for (Edge<T> *adjacent : node->getAdjacent()) {
        if (!adjacent->getTarget()->isVisited()) {
            dfsVisit(adjacent->getTarget(), targets, found);
        }
    }
}

#endif //FEUP_CAL_PARKING_SEARCH_H
