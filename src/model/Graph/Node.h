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

    void addEdge(id_t id, Node<T> *target, double weight);

    void removeEdge(Node<T> *target);

    std::vector<Edge<T> *> getAdjacent();

    T getElement();

    bool isVisited();

    void setVisited();

    void setUnvisited();

    id_t getId() const;

private:
    T _element;
    char _helpers;
    std::vector<Edge<T> *> _adjacentEdges;
    id_t _id;
};

template<class T>
Node<T>::Node(id_t id, T element) : _id(id), _element(element) {

}

template<class T>
void Node<T>::addEdge(id_t id, Node<T> *target, double weight) {
    _adjacentEdges.push_back(new Edge<T>(id, target, weight));
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
std::vector<Edge<T> *> Node<T>::getAdjacent() {
    return _adjacentEdges;
}

template<class T>
T Node<T>::getElement() {
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


#endif //FEUP_CAL_PARKING_NODE_H
