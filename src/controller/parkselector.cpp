#include <stdexcept>
#include "parkselector.h"
#include "../algorithms/search.hpp"
#include "../algorithms/shortestdistance.hpp"

static std::vector<Node<MapPoint>*> candidateParks(const Graph<MapPoint>& graph, Node<MapPoint>* point, double maxDistance){
    if (point->getElement().isPark()) return {};
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

static double parkEvaluation(Graph<MapPoint>& graph, Node<MapPoint>* point, Node<MapPoint>* park, Node<MapPoint>* sourceNode,
                             Node<MapPoint>* endNode, float i, float j, float k, double maxEuclideanDistance){
    if (!park->getElement().isPark()) {
        throw std::invalid_argument("Node is not a park");
    }
    if (i+j+k < 0.99 || i+j+k > 1.01){
        throw std::invalid_argument("Factors must add up to 1");
    }
    auto parkFields = park->getElement().getParkFields();
    double priceEval = parkFields.fixedPrice +
            (((double)parkFields.capacity-parkFields.freeSpots)/parkFields.capacity)*parkFields.capacityTaxFactor;
    if (priceEval > 10) priceEval = 10; // relax price evaluation
    priceEval /= 10;

    AStar(park->getElement(), graph, endNode->getElement());
    double distanceToDestiny = distance(getAStarPath(graph, park->getElement(), endNode->getElement()));
    auto fromSourceDist = sourceNode->getElement().euclideanDistance(endNode->getElement());
    if (distanceToDestiny > 10*fromSourceDist) distanceToDestiny = 10*fromSourceDist;
    distanceToDestiny /= 10*fromSourceDist;

    AStar(point->getElement(), graph, park->getElement());
    double walkDistance = distance(getAStarPath(graph, point->getElement(), park->getElement()));
    if (walkDistance > 10*maxEuclideanDistance) walkDistance = 10*maxEuclideanDistance;
    walkDistance /= 10*maxEuclideanDistance;

    return i*priceEval + j*walkDistance + k*distanceToDestiny;
}

std::vector<Node<MapPoint>*>
getPathAfterParkReplacement(Graph<MapPoint>& graph, const std::vector<Node<MapPoint>*>& stopPoints, Node<MapPoint>* sourceNode, Node<MapPoint>* endNode,
                            std::vector<bool> shallPark, float iFactor, float jFactor, float kFactor, double maxEuclideanDistance){
    if (stopPoints.size() != shallPark.size()){
        throw std::invalid_argument("Whether to stop on each park must be specified");
    }
    auto finalPath = stopPoints;
    for (int i = 0; i < stopPoints.size(); i++){
        if (!shallPark.at(i)) continue;
        auto parks = candidateParks(graph, stopPoints.at(i), maxEuclideanDistance);
        if (parks.empty()) continue;
        Node<MapPoint>* bestPark = parks.at(0);
        double bestEval = parkEvaluation(graph, stopPoints.at(i), bestPark, sourceNode, endNode, iFactor, jFactor, kFactor, maxEuclideanDistance);
        for (int j = 1; j < parks.size(); j++){
            double eval = parkEvaluation(graph, stopPoints.at(i), parks.at(j), sourceNode, endNode, iFactor, jFactor, kFactor, maxEuclideanDistance);
            if (eval < bestEval){
                bestEval = eval;
                bestPark = parks.at(i);
            }
        }
        finalPath.at(i) = bestPark;
    }
    return finalPath;
}

std::vector<std::vector<Node<MapPoint>*>> getWalkPaths(Graph<MapPoint>& graph, const std::vector<Node<MapPoint>*>& stopPoints,
                                          const std::vector<Node<MapPoint>*>& actualStops){
    if (stopPoints.size() != actualStops.size()){
        throw std::invalid_argument("Stopping vector size does not make sense");
    }
    std::vector<std::vector<Node<MapPoint>*>> paths;
    paths.resize(stopPoints.size(), {});
    for (int i = 0; i < stopPoints.size(); i++){
        if (stopPoints.at(i)->getElement() == actualStops.at(i)->getElement()
            || stopPoints.at(i)->getElement().isPark()){
            continue;
        } else {
            dijkstra(stopPoints.at(i)->getElement(), graph);
            paths.at(i) = getDijkstraPath(graph, stopPoints.at(i)->getElement(), actualStops.at(i)->getElement());
        }
    }
    for (int i = 0; i < paths.size(); i++){
        if (paths.at(i).empty()) continue;
        if (paths.at(i).at(0)->getElement() != stopPoints.at(i)->getElement()
            || paths.at(i).at(paths.at(i).size()-1)->getElement() != actualStops.at(i)->getElement()){
            throw std::logic_error("Error calculating walk paths");
        }
    }
    return paths;
}
