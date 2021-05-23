#ifndef FEUP_CAL_PARKING_NODE_HPP
#define FEUP_CAL_PARKING_NODE_HPP

#include <vector>
#include <algorithm>
#include "Edge.hpp"

#define BIT(n) (1 << (n))
#define VISITED BIT(0)

template<class T>
class Node {
public:
    Node(id_t id, T element);

    Edge<T>* addEdge(id_t id, Node<T> *target, double weight);

    void removeEdge(Node<T> *target);

    std::vector<Edge<T> *> getAdjacent() const;

    double getDist() const;

    Node<T>* getPath() const;

    T getElement() const;

    bool isVisited();

    void setVisited();

    void setDist(double newDist);

    void setPath(Node<T> *path);

    void setUnvisited();

    id_t getId() const;

    bool operator==(const Node<T>& node) const;

    bool operator<(const Node<T>& node) const;

    void sortAdjacentEdges();

    unsigned int queueIndex = 0;

private:
    T _element;
    char _helpers;
    std::vector<Edge<T> *> _adjacentEdges;
    double dist = 0;
    Node<T> *path = NULL;
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

double Node<T>::getDist() const{
    return dist;
}

template<class T>
Node<T> *Node<T>::getPath() const{
    return path;
}

template<class T>
void Node<T>::setDist(double newDist) {
    dist = newDist;
}

template<class T>
void Node<T>::setPath(Node<T>* newPath) {
    path = newPath;
}

template<class T>
bool Node<T>::operator==(const Node<T>& node) const {
    return this->getElement() == node.getElement() && this->getId() == node.getId();
}

template<class T>
void Node<T>::sortAdjacentEdges(){
    std::sort(_adjacentEdges.begin(), _adjacentEdges.end(), [](const Edge<T>* e1, const Edge<T>* e2) {
        return e1->getWeight() < e2->getWeight();
    });
}

template<class T>
bool Node<T>::operator<(const Node<T> &node) const {
    return this->dist < node.dist;
}


#endif //FEUP_CAL_PARKING_NODE_HPP
