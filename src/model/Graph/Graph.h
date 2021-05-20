#ifndef FEUP_CAL_PARKING_GRAPH_H
#define FEUP_CAL_PARKING_GRAPH_H

#include <vector>
#include <stdexcept>
#include <unordered_map>
#include <iostream>
#include "Node.h"
#include "Edge.h"

template<class T>
class Graph {
public:

    void reserveNumberNodes(size_t numberNodes);

    Node<T> *addNode(id_t id, const T &element);

    void removeNode(const T &element);

    Edge<T> *addEdge(id_t id, Node<T> *source, Node<T> *target, double weight);

    void removeEdge(const T &source, const T &target);

    size_t getNumberOfNodes() const;

    std::vector<Node<T> *> getNodes() const;

    Node<T> *findNodeById(id_t id);

    Graph<T> getTransposed() const;

private:
    std::vector<Node<T> *> _nodes;
    std::unordered_map<id_t, Node<T> *> _ids;

    Node<T> *findNode(const T &element);

};

template<class T>
Node<T> *Graph<T>::addNode(id_t id, const T &element) {
    if (findNodeById(id) != nullptr) {
        throw std::logic_error("Node already exists");
    }
    auto node = new Node<T>(id, element);
    _ids[id] = node;
    _nodes.push_back(node);
    return node;
}

template<class T>
Node<T> *Graph<T>::findNode(const T &element) {
    auto node = std::find_if(_nodes.begin(), _nodes.end(), [element](Node<T> *node) {
        return node->getElement() == element;
    });
    return node != _nodes.end() ? *node : nullptr;
}

template<class T>
void Graph<T>::removeNode(const T &element) {
    auto node = findNode(element);
    if (node == nullptr) {
        throw std::logic_error("Node does not exist");
    }
    for (auto it = _nodes.begin(); it != _nodes.end(); it++) {
        if (*it == node) {
            _nodes.erase(it);
            return;
        }
    }
}

template<class T>
void Graph<T>::removeEdge(const T &source, const T &target) {
    for (auto &n : _nodes) {
        if (n->getElement() != source) continue;
        auto adj = n->getAdjacent();
        for (auto it = adj.begin(); it != adj.end(); it++) {
            if ((*it)->getTarget()->getElement() == target) {
                n->removeEdge((*it)->getTarget());
                return;
            }
        }
    }
    throw std::logic_error("Edge does not exist");
}

template<class T>
size_t Graph<T>::getNumberOfNodes() const {
    return _nodes.size();
}

template<class T>
std::vector<Node<T> *> Graph<T>::getNodes() const {
    return _nodes;
}

template<class T>
Node<T> *Graph<T>::findNodeById(id_t id) {
    return _ids.find(id) != _ids.end() ? _ids.at(id) : nullptr;
}

template<class T>
Edge<T> *Graph<T>::addEdge(id_t id, Node<T> *source, Node<T> *target, double weight) {
    if (source == nullptr) {
        throw std::logic_error("Source node does not exist");
    }
    if (target == nullptr) {
        throw std::logic_error("Target node does not exist");
    }
    return source->addEdge(id, target, weight);
}

template<class T>
void Graph<T>::reserveNumberNodes(size_t numberNodes) {
    if (!_nodes.empty() || !_ids.empty()) {
        throw std::logic_error("Cannot reserve space on non empty graph");
    }
    _nodes.reserve(numberNodes);
    _ids.reserve(numberNodes);
}

template<class T>
Graph<T> Graph<T>::getTransposed() const {
    Graph<T> transposed{};
    for (Node<T> *node : _nodes) {
        auto newNode = transposed.addNode(node->getId(), node->getElement());
        for (Edge<T> *edge : node->getAdjacent()) {
            transposed.addEdge(edge->getId(), edge->getTarget(), newNode, edge->getWeight());
        }
    }
    return transposed;
}


#endif //FEUP_CAL_PARKING_GRAPH_H
