#ifndef FEUP_CAL_PARKING_NODE_H
#define FEUP_CAL_PARKING_NODE_H

#include <vector>
#include <algorithm>
#include "Edge.h"

template <class T>
class Node {
public:
    explicit Node(T element);
    void addEdge(Node<T>* target, double weight);
    void removeEdge(Node<T>* target);
    std::vector<Edge<T>*> getAdjacent();
    T getElement();
private:
    T _element;
    std::vector<Edge<T>*> _adjacentEdges;
};

template<class T>
Node<T>::Node(T element) : _element(element){

}

template<class T>
void Node<T>::addEdge(Node<T>* target, double weight) {
    _adjacentEdges.push_back(new Edge<T>(target, weight));
}

template<class T>
void Node<T>::removeEdge(Node<T> *target) {
    for (auto it = _adjacentEdges.begin(); it != _adjacentEdges.end(); it++){
        if ((*it)->getTarget()->getElement() == target->getElement()){
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


#endif //FEUP_CAL_PARKING_NODE_H