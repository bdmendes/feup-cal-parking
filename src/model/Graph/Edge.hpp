#ifndef FEUP_CAL_PARKING_EDGE_HPP
#define FEUP_CAL_PARKING_EDGE_HPP

template<class T>
class Node;

template<class T>
class Edge {
public:
    Edge(id_t id, Node<T> *target, double weight);

    Node<T> *getTarget() const;

    double getWeight() const;

    void setWeight(double weight);

    id_t getId() const;

    bool operator==(const Edge<T>& edge) const;

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
Node<T> *Edge<T>::getTarget() const {
    return _target;
}

template<class T>
double Edge<T>::getWeight() const {
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

template<class T>
bool Edge<T>::operator==(const Edge<T> &edge) const {
    return _id == edge.getId();
}


#endif //FEUP_CAL_PARKING_EDGE_HPP
