#ifndef FEUP_CAL_PARKING_EDGE_H
#define FEUP_CAL_PARKING_EDGE_H

template<class T>
class Node;

template<class T>
class Edge {
public:
    Edge(id_t id, Node<T> *target, double weight);

    Node<T> *getTarget();

    double getWeight();

    void setWeight(double weight);

    id_t getId() const;

private:
    id_t _id;
    double _weight;
    Node<T> *_target;
};

template<class T>
Edge<T>::Edge(id_t id, Node<T> *target, double weight)
        : _id(id), _target(target), _weight(weight) {

}

template<class T>
Node<T> *Edge<T>::getTarget() {
    return _target;
}

template<class T>
double Edge<T>::getWeight() {
    return _weight;
}

template<class T>
void Edge<T>::setWeight(double weight) {
    _weight = weight;
}

template<class T>
id_t Edge<T>::getId() const {
    return _id;
}


#endif //FEUP_CAL_PARKING_EDGE_H
