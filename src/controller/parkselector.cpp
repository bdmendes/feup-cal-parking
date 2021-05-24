#include <stdexcept>
#include "parkselector.h"
#include "../algorithms/search.hpp"
#include "../algorithms/shortestdistance.hpp"

static std::vector<Node<MapPoint>*> candidateParks(const Graph<MapPoint>& graph, Node<MapPoint>* point, double maxDistance){
    std::vector<Node<MapPoint>*> parks;
    for (const auto& node: graph.getNodes()){
        if (node->getElement().isPark() && node->getElement().euclideanDistance(point->getElement()) <= maxDistance){
            std::vector<Node<MapPoint>*> targets = {graph.findNode(node->getElement())};
            auto found = dfsFromNode(point, targets, graph);
            if (!found.empty()){
                parks.push_back(node);
            }
        }
    }
    return parks;
}

static double parkEvaluation(const Graph<MapPoint>& graph, Node<MapPoint>* point,
                             Node<MapPoint>* park, Node<MapPoint>* endNode, int i, int j, int k){
    if (!park->getElement().isPark()) {
        throw std::invalid_argument("Node is not a park");
    }
    auto parkFields = park->getElement().getParkFields();
    double priceEval = parkFields.fixedPrice +
            (((double)parkFields.capacity-parkFields.freeSpots)/parkFields.capacity)*parkFields.capacityTaxFactor;

    AStar(park->getElement(), graph, endNode->getElement());
    double distanceToDestiny = distance(getAStarPath(graph, park->getElement(), endNode->getElement()));

    AStar(point->getElement(), graph, park->getElement());
    double walkDistance = distance(getAStarPath(graph, point->getElement(), park->getElement()));

    return i*priceEval + j*walkDistance + k*distanceToDestiny;
}

std::vector<Node<MapPoint>*>
getPathAfterParkReplacement(const Graph<MapPoint>& graph, const std::vector<Node<MapPoint>*>& stopPoints, Node<MapPoint>* endNode,
                            const std::vector<bool>& shallPark, int iFactor, int jFactor, int kFactor, double maxDistance){
    if (stopPoints.size() != shallPark.size()){
        throw std::invalid_argument("Whether to stop on each park must be specified");
    }
    auto finalPath = stopPoints;
    for (int i = 0; i < stopPoints.size(); i++){
        if (!shallPark.at(i)) continue;
        auto parks = candidateParks(graph, stopPoints.at(i), maxDistance);
        if (parks.empty()) continue;
        Node<MapPoint>* bestPark = parks.at(0);
        double bestEval = parkEvaluation(graph, stopPoints.at(i), bestPark, endNode, iFactor, jFactor, kFactor);
        for (int j = 1; j < parks.size(); j++){
            double eval = parkEvaluation(graph, stopPoints.at(i), parks.at(j), endNode, iFactor, jFactor, kFactor);
            if (eval < bestEval){
                bestEval = eval;
                bestPark = parks.at(i);
            }
        }
        finalPath.at(i) = bestPark;
    }
    return finalPath;
}
