#ifndef FEUP_CAL_PARKING_SEARCH_HPP
#define FEUP_CAL_PARKING_SEARCH_HPP

#include <queue>
#include "../model/Graph/Graph.hpp"
#include "algorithm"

template<class T>
static void dfsVisit(Node<T> *node, const std::vector<Node<T> *> &targets, std::vector<Node<T> *> &found) {
    if (found.size() == targets.size()) return;
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

template<class T>
inline std::vector<Node<T> *> dfsAll(const std::vector<Node<T> *> &targets, const Graph<T> &graph) {
    std::vector<Node<T> *> res{};
    for (Node<T> *node : graph.getNodes()) {
        node->setUnvisited();
    }
    for (Node<T> *node : graph.getNodes()) {
        if (res.size() == targets.size()) {
            break;
        }
        if (!node->isVisited()) {
            dfsVisit(node, targets, res);
        }
    }
    return res;
}

template<class T>
inline std::vector<Node<T> *> dfsFromNode(Node<T> *source, const std::vector<Node<T> *> &targets, const Graph<T> &graph) {
    std::vector<Node<T> *> res{};
    for (Node<T> *node : graph.getNodes()) {
        node->setUnvisited();
    }
    dfsVisit(source, targets, res);
    return res;
}

template<class T>
inline std::vector<Node<T> *> bfs(Node<T> *source, const std::vector<Node<T> *> &targets, const Graph<T> &graph) {
    std::vector<Node<T> *> res{};
    for (Node<T> *node : graph.getNodes()) {
        node->setUnvisited();
    }
    std::queue<Node<T> *> queue{};
    queue.push(source);
    source->setVisited();
    while (!queue.empty()) {
        if (targets.size() == res.size()) {
            break;
        }
        Node<T> *node = queue.front();
        queue.pop();
        for (Edge<T> *adjacent : node->getAdjacent()) {
            if (!adjacent->getTarget()->isVisited()) {
                adjacent->getTarget()->setVisited();
                bool isTarget = std::find_if(targets.begin(), targets.end(), [&](Node<T> *n1) {
                    return n1->getElement() == node->getElement();
                }) != targets.end();
                if (isTarget) {
                    res.push_back(adjacent->getTarget());
                }
                queue.push(adjacent->getTarget());
            }
        }
    }
    return res;
}

template<class T>
inline bool kosaraju(const Graph<T> &graph) {
    for (Node<T> *node : graph.getNodes()) {
        node->setUnvisited();
    }
    Node<T> *startingNode = graph.getNodes().front();
    std::vector<Node<T> *> visited = dfsFromNode(startingNode, graph.getNodes(), graph);
    if (visited.size() != graph.getNodes().size()) {
        return false;
    }
    Graph<T> transposed = graph.getTransposed();
    for (Node<T> *node : transposed.getNodes()) {
        node->setUnvisited();
    }
    startingNode = transposed.getNodes().front();
    visited = dfsFromNode(startingNode, transposed.getNodes(), transposed);
    if (visited.size() != transposed.getNodes().size()) {
        return false;
    }

    return true;
}


#endif //FEUP_CAL_PARKING_SEARCH_HPP
