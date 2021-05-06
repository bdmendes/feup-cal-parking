#ifndef FEUP_CAL_PARKING_GRAPH_H
#define FEUP_CAL_PARKING_GRAPH_H

#include <vector>
#include <stdexcept>

#include "Node.h"
#include "Edge.h"

template <class T>
class Graph {
public:
    void addNode(const T& element);
    void removeNode(const T& element);
    void addEdge(const T& source, const T& target, double weight);
    void removeEdge(const T& source, const T& target);
    int getNumberOfNodes() const;
    std::vector<Node<T>*> getNodes() const;
private:
    std::vector<Node<T>*> _nodes;
    Node<T>* findNode(const T& element);
};

template<class T>
void Graph<T>::addNode(const T &element) {
    if (findNode(element) != nullptr){
        throw std::logic_error("Node already exists");
    }
    _nodes.push_back(new Node<T>(element));
}

template<class T>
Node<T> *Graph<T>::findNode(const T &element) {
    for (auto it = _nodes.begin(); it != _nodes.end(); it++){
        if ((*it)->getElement() == element){
            return *it;
        }
    }
    return nullptr;
}

template<class T>
void Graph<T>::removeNode(const T &element) {
    auto node = findNode(element);
    if (node == nullptr){
        throw std::logic_error("Node does not exist");
    }
    for (auto it = _nodes.begin(); it != _nodes.end(); it++){
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
    if (sourceNode == nullptr){
        throw std::logic_error("Source node does not exist");
    } else if (targetNode == nullptr){
        throw std::logic_error("Target node does not exist");
    }
    sourceNode->addEdge(targetNode, weight);
}

template<class T>
void Graph<T>::removeEdge(const T &source, const T &target) {
    for (auto& n : _nodes){
        if (n->getElement() != source) continue;
        auto adj = n->getAdjacent();
        for (auto it = adj.begin(); it != adj.end(); it++){
            if ((*it)->getTarget()->getElement() == target){
                n->removeEdge((*it)->getTarget());
                return;
            }
        }
    }
    throw std::logic_error("Edge does not exist");
}

template<class T>
int Graph<T>::getNumberOfNodes() const {
    return _nodes.size();
}

template<class T>
std::vector<Node<T> *> Graph<T>::getNodes() const {
    return _nodes;
}


#endif //FEUP_CAL_PARKING_GRAPH_H
