#ifndef FEUP_CAL_PARKING_TSP_H
#define FEUP_CAL_PARKING_TSP_H

#include "../model/Graph/Graph.h"
#include <algorithm>
#include <limits.h>

template <class T>
double tspNearestNeighbour(Node<T>* source, const std::vector<Node<T>*>& intermediate, Node<T>* target,
                                std::vector<Node<T>*>& foundIntermediate){
    foundIntermediate = std::vector<Node<T>*>();
    double totalDistance = 0;

    for (Node<T>* curr = source;;){
        curr->sortAdjacentEdges();
        Node<T>* next = nullptr;
        for (const auto& edge: curr->getAdjacent()){
            auto candidateNext = edge->getTarget();
            auto distance = edge->getWeight();
            if (target->getElement() == source->getElement()){
                continue;
            } else if (target->getElement() == candidateNext->getElement()) {
                if (foundIntermediate.size() == intermediate.size()) {
                    totalDistance += distance;
                    return totalDistance;
                }
            } else {
                auto isToVisit = std::find_if(intermediate.begin(), intermediate.end(), [candidateNext](Node<T> *n) {
                    return n->getElement() == candidateNext->getElement();
                }) != intermediate.end();
                auto wasAlreadyVisited =
                        std::find_if(foundIntermediate.begin(), foundIntermediate.end(), [candidateNext](Node<T> *n) {
                            return n->getElement() == candidateNext->getElement();
                        }) != foundIntermediate.end();
                if (isToVisit && !wasAlreadyVisited) {
                    totalDistance += distance;
                    next = candidateNext;
                    foundIntermediate.push_back(next);
                    break;
                }
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

template <class T>
double tspBruteForce(Node<T>* source, const std::vector<Node<T>*>& intermediate, Node<T>* target,
                           std::vector<Node<T>*>& foundIntermediate) {
    double bestDist = INT_MAX;
    std::vector<Node<T>*> bestTravel;
    std::vector<Node<T>*> points = intermediate;
    do {
        double currDist = 0;
        bool possible = true;
        for (int i = 0; i < points.size(); i++){
            if (i == 0){
                auto sourceAdjacent = source->getAdjacent();
                auto edge = std::find_if(sourceAdjacent.begin(), sourceAdjacent.end(), [points](const Edge<T>* e){
                    return e->getTarget()->getElement() == points.at(0)->getElement();
                });
                if (edge == sourceAdjacent.end()){
                    possible = false;
                    break;
                } else {
                    currDist += (*edge)->getWeight();
                }
            } else if (i == points.size()-1){
                auto lastAdjacent = points.at(i)->getAdjacent();
                auto edge = std::find_if(lastAdjacent.begin(), lastAdjacent.end(), [target](const Edge<T>* e){
                    return e->getTarget()->getElement() == target->getElement();
                });
                if (edge == lastAdjacent.end()){
                    possible = false;
                    break;
                } else {
                    currDist += (*edge)->getWeight();
                }
            }

            if (i < points.size()-1){
                auto adjacent = points.at(i)->getAdjacent();
                auto nextNode = points.at(i+1);
                auto edge = std::find_if(adjacent.begin(), adjacent.end(), [nextNode](const Edge<T>* e){
                    return e->getTarget()->getElement() == nextNode->getElement();
                });
                if (edge == adjacent.end()){
                    possible = false;
                    break;
                } else {
                    currDist += (*edge)->getWeight();
                }
            }
        }

        if (possible && currDist < bestDist){
            bestDist = currDist;
            bestTravel = points;
        }
    } while (std::next_permutation(points.begin(), points.end()));

    if (!bestTravel.empty()){
        foundIntermediate = bestTravel;
        return bestDist;
    } else {
        throw std::logic_error("Could not found a valid travel");
    }
}

#endif //FEUP_CAL_PARKING_TSP_H
