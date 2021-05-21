#ifndef FEUP_CAL_PARKING_NODE_H
#define FEUP_CAL_PARKING_NODE_H

#include <vector>
#include <algorithm>
#include "Edge.h"

#define BIT(n) (1 << (n))
#define VISITED BIT(0)

template<class T>
class Node {
public:
    Node(id_t id, T element);

    Edge<T>* addEdge(id_t id, Node<T> *target, double weight);

    void removeEdge(Node<T> *target);

    std::vector<Edge<T> *> getAdjacent() const;

    T getElement() const;

    bool isVisited();

    void setVisited();

    void setUnvisited();

    id_t getId() const;

    bool operator==(const Node<T>& node) const;

private:
    T _element;
    char _helpers;
    std::vector<Edge<T> *> _adjacentEdges;
    id_t _id;
};

template<class T>
Node<T>::Node(id_t id, T element) : _id(id), _element(element), _helpers(0x0) {

}

template<class T>
Edge<T>* Node<T>::addEdge(id_t id, Node<T> *target, double weight) {
    auto edge = new Edge<T>(id, target, weight);
    _adjacentEdges.push_back(edge);
    return edge;
}

template<class T>
void Node<T>::removeEdge(Node<T> *target) {
    for (auto it = _adjacentEdges.begin(); it != _adjacentEdges.end(); it++) {
        if ((*it)->getTarget()->getElement() == target->getElement()) {
            _adjacentEdges.erase(it);
            return;
        }
    }
}

template<class T>
std::vector<Edge<T> *> Node<T>::getAdjacent() const{
    return _adjacentEdges;
}

template<class T>
T Node<T>::getElement() const{
    return _element;
}

template<class T>
bool Node<T>::isVisited() {
    return _helpers & VISITED;
}

template<class T>
void Node<T>::setVisited() {
    _helpers |= VISITED;
}

template<class T>
void Node<T>::setUnvisited() {
    _helpers &= ~VISITED;
}

template<class T>
id_t Node<T>::getId() const {
    return _id;
}

template<class T>
bool Node<T>::operator==(const Node<T>& node) const {
    return this->getElement() == node.getElement();
}


#endif //FEUP_CAL_PARKING_NODE_H
