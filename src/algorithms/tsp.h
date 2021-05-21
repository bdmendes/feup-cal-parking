#ifndef FEUP_CAL_PARKING_TSP_H
#define FEUP_CAL_PARKING_TSP_H

#include "../model/Graph/Graph.h"

template <class T>
double void tspNearestNeighbour(const Graph<T>& graph, const Node<T>* source,
                                const std::vector<Node<T>*> intermediate, const Node<T>* target,
                                std::vector<Node<T>>& foundIntermediate){
    auto sourceNode = graph.findNode(source->getElement());
    if (sourceNode == nullptr) throw std::invalid_argument("Source node not found");
    foundIntermediate = std::vector<Node<T>*>();
    double totalDistance = 0f;

    for (Node<T>* curr = src;;){
        auto adjacentEdges = curr->getAdjacent();
        std::sort(adjacentEdges.begin(), adjacentEdges.end(), [](const Edge<T>* e1, const Edge<T>* e2) const {
            return e1->getWeight() < e2->getWeight();
        });

        Node<T>* next = nullptr;
        for (auto it = adjacentEdges.begin(); it != adjacentEdges.end(); it++){
            auto targetNode = (*it)->getTarget();
            auto distance = (*it)->getWeight();

            if (target->getElement() == sourceNode->getElement()){
                continue;
            }

            if (target->getElement() == targetNode->getElement()){
                if (foundIntermediate.size() == intermediate){
                    totalDistance += distance;
                    return;
                } else {
                    continue;
                }
            }

            auto isToVisit = std::find_if(intermediate.begin(), intermediate.end(), [targetNode](Node<T>* n) const {
                return n->getElement() == targetNode->getElement();
            }) != intermediate.end();
            auto wasAlreadyVisited = std::find_if(foundIntermediate.begin(), foundIntermediate.end(), [targetNode](Node<T>* n) const {
                return n->getElement() == targetNode->getElement();
            }) != intermediate.end();
            if (isToVisit && !wasAlreadyVisited){
                totalDistance += distance;
                next = targetNode;
                foundIntermediate.push_back(next);
                break;
            }
        }

        if (next == nullptr){
            throw std::logic_error("Could not found a valid travel");
        } else {
            break;
        }
    }

    return totalDistance;
}

#endif //FEUP_CAL_PARKING_TSP_H
