#ifndef FEUP_CAL_PARKING_GRAPH_H
#define FEUP_CAL_PARKING_GRAPH_H

#include <vector>
#include <stdexcept>
#include "Node.h"
#include "Edge.h"

template<class T>
class Graph {
public:
    void addNode(size_t id, const T &element);

    void removeNode(const T &element);

    void addEdge(const T &source, const T &target, double weight);

    void addEdge(Node<T> *source, Node<T> *target, double weight);

    void removeEdge(const T &source, const T &target);

    size_t getNumberOfNodes() const;

    std::vector<Node<T> *> getNodes() const;

    Node<T> *findNodeById(size_t id);

private:
    std::vector<Node<T> *> _nodes;

    Node<T> *findNode(const T &element);

    std::pair<double, double> minCoords;
    std::pair<double, double> maxCoords;
};

template<class T>
void Graph<T>::addNode(size_t id, const T &element) {
    if (findNodeById(id) != nullptr) {
        throw std::logic_error("Node already exists");
    }
    _nodes.push_back(new Node<T>(id, element));
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
Node<T> *Graph<T>::findNodeById(size_t id) {
    for (auto it = _nodes.begin(); it != _nodes.end(); it++) {
        if ((*it)->getId() == id) {
            return *it;
        }
    }
    return nullptr;
}

template<class T>
void Graph<T>::addEdge(Node<T> *source, Node<T> *target, double weight) {
    if (source == nullptr) {
        throw std::logic_error("Source node does not exist");
    } else if (target == nullptr) {
        throw std::logic_error("Target node does not exist");
    }
    source->addEdge(target, weight);
}


#endif //FEUP_CAL_PARKING_GRAPH_H
