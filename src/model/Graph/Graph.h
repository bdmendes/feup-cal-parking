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

    void addNode(id_t id, const T &element);

    void removeNode(const T &element);

    void addEdge(const T &source, const T &target, double weight);

    void addEdge(id_t id, Node<T> *source, Node<T> *target, double weight);

    void removeEdge(const T &source, const T &target);

    size_t getNumberOfNodes() const;

    std::vector<Node<T> *> getNodes() const;

    Node<T> *findNodeById(id_t id);

private:
    std::vector<Node<T> *> _nodes;
    std::unordered_map<id_t, Node<T> *> _ids;

    Node<T> *findNode(const T &element);

};

template<class T>
void Graph<T>::addNode(id_t id, const T &element) {
    if (findNodeById(id) != nullptr) {
        throw std::logic_error("Node already exists");
    }
    auto node = new Node<T>(id, element);
    _ids[id] = node;
    _nodes.push_back(node);
}

template<class T>
Node<T> *Graph<T>::findNode(const T &element) {
    for (auto it = _nodes.begin(); it != _nodes.end(); it++) {
        if ((*it)->getElement() == element) {
            return *it;
        }
    }
    return nullptr;
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
            break;
        }
    }
}

template<class T>
void Graph<T>::addEdge(const T &source, const T &target, double weight) {
    auto sourceNode = findNode(source);
    auto targetNode = findNode(target);
    if (sourceNode == nullptr) {
        throw std::logic_error("Source node does not exist");
    } else if (targetNode == nullptr) {
        throw std::logic_error("Target node does not exist");
    }
    sourceNode->addEdge(targetNode, weight);
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
void Graph<T>::addEdge(id_t id, Node<T> *source, Node<T> *target, double weight) {
    if (source == nullptr) {
        throw std::logic_error("Source node does not exist");
    } else if (target == nullptr) {
        throw std::logic_error("Target node does not exist");
    }
    source->addEdge(id, target, weight);
}

template<class T>
void Graph<T>::reserveNumberNodes(size_t numberNodes) {
    if (_nodes.size() > numberNodes) {
        throw std::logic_error("Nodes vector is too big");
    }
    _nodes.reserve(numberNodes);
}


#endif //FEUP_CAL_PARKING_GRAPH_H
