#ifndef FEUP_CAL_PARKING_TSP_H
#define FEUP_CAL_PARKING_TSP_H

#include "../model/Graph/Graph.h"
#include <algorithm>

template <class T>
double tspNearestNeighbour(const Graph<T>& graph, const Node<T>* source,
                                const std::vector<Node<T>*>& intermediate, const Node<T>* target,
                                std::vector<Node<T>*>& foundIntermediate){
    auto sourceNode = graph.findNode(source->getElement());
    if (sourceNode == nullptr) throw std::invalid_argument("Source node not found");
    foundIntermediate = std::vector<Node<T>*>();
    double totalDistance = 0;

    for (Node<T>* curr = sourceNode;;){
        curr->sortAdjacentEdges();
        Node<T>* next = nullptr;
        for (const auto& edge: curr->getAdjacent()){
            auto candidateNext = edge->getTarget();
            auto distance = edge->getWeight();

            if (target->getElement() == sourceNode->getElement()){
                continue;
            }

            if (target->getElement() == candidateNext->getElement()){
                if (foundIntermediate.size() == intermediate.size()){
                    totalDistance += distance;
                    return totalDistance;
                } else {
                    continue;
                }
            }

            auto isToVisit = std::find_if(intermediate.begin(), intermediate.end(), [candidateNext](Node<T>* n) {
                return n->getElement() == candidateNext->getElement();
            }) != intermediate.end();
            auto wasAlreadyVisited = std::find_if(foundIntermediate.begin(), foundIntermediate.end(), [candidateNext](Node<T>* n) {
                return n->getElement() == candidateNext->getElement();
            }) != foundIntermediate.end();
            if (isToVisit && !wasAlreadyVisited){
                totalDistance += distance;
                next = candidateNext;
                foundIntermediate.push_back(next);
                break;
            }
        }

        if (next == nullptr){
            throw std::logic_error("Could not found a valid travel");
        } else {
            curr = next;
            continue;
        }
    }

    return totalDistance;
}

#endif //FEUP_CAL_PARKING_TSP_H
