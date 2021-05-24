#include <stdexcept>
#include "parkselector.h"

/*static std::vector<MapPoint*> getCandidateParks(const Graph<MapPoint>& graph, const MapPoint& point, double maxDistance){
    for (const auto& node: graph.getNodes()){
        if (node->getElement().isPark() && node->getElement())
    }
}*/

std::vector<MapPoint*> getPathAfterParkReplacement(const Graph<MapPoint>& graph, const MapPoint& source, const MapPoint& target,
                                                   const std::vector<MapPoint*>& stopPoints, const std::vector<bool>& shallPark,
                                                   std::vector<double>& parkDistance, std::vector<std::vector<MapPoint*>>& parkWalkPaths,
                                                   int i, int j, int k, double maxDistance){
    if (stopPoints.size() != shallPark.size()){
        throw std::invalid_argument("Whether to stop on each park must be specified");
    }

}
