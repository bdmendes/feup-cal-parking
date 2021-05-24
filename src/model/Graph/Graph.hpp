#ifndef FEUP_CAL_PARKING_GRAPH_HPP
#define FEUP_CAL_PARKING_GRAPH_HPP

#include <vector>
#include <stdexcept>
#include <unordered_map>
#include <iostream>
#include "Node.hpp"
#include "Edge.hpp"

template<class T>
class Graph {
public:
    Graph();

    virtual Node<T> *addNode(id_t id, const T &element);

    virtual void removeNode(const T &element);

    virtual Edge<T> *addEdge(id_t id, Node<T> *source, Node<T> *target, double weight);

    virtual void removeEdge(const T &source, const T &target);

    void reserveNumberNodes(size_t numberNodes);

    size_t getNumberOfNodes() const;

    std::vector<Node<T> *> getNodes() const;

    Node<T> *findNodeById(id_t id) const;

    Node<T> *findNode(const T &element) const;

    Graph<T> getTransposed() const;

    std::vector<std::vector<double>> getAdjacencyMatrix() const;

protected:
    id_t getMaxId() const;
    std::vector<Node<T> *> _nodes;
    std::unordered_map<id_t, Node<T> *> _ids;
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
Node<T> *Graph<T>::findNode(const T &element) const {
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
    throw std::logic_error("Node does not exist");
}

template<class T>
void Graph<T>::removeEdge(const T &source, const T &target) {
    for (auto &n : _nodes) {
        if (n->getElement() != source) continue;
        auto adj = n->getAdjacent();
        for (auto& it : adj) {
            if (it->getTarget()->getElement() == target) {
                n->removeEdge(it->getTarget());
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
Node<T> *Graph<T>::findNodeById(id_t id) const {
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

template<class T>
Graph<T>::Graph() : _nodes{}, _ids{} {
}

template<class T>
std::vector<std::vector<double>> Graph<T>::getAdjacencyMatrix() const {
    int size = getMaxId() + 1;
    std::vector<std::vector<double>> matrix(size, std::vector<double>());
    for (auto& l : matrix) {
        l.resize(size, UINT32_MAX);
    }
    for (auto& node : _nodes){
        id_t srcID = node->getId();
        auto adj = node->getAdjacent();
        for (auto& edge : adj){
            id_t targetID = edge->getTarget()->getId();
            matrix.at(srcID).at(targetID) = edge->getWeight();
        }
    }
    return matrix;
}

template<class T>
id_t Graph<T>::getMaxId() const {
    id_t maxId = 0;
    for (const auto& node : _nodes){
        if (node->getId() > maxId){
            maxId = node->getId();
        }
    }
    return maxId;
}

#endif //FEUP_CAL_PARKING_GRAPH_HPP
