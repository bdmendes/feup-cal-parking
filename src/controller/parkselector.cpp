#include <stdexcept>
#include "parkselector.h"

std::vector<MapPoint*> getPathAfterParkReplacement(const MapPoint& source, const MapPoint& target,
                                                   const std::vector<MapPoint*>& stopPoints, const std::vector<bool>& shallPark,
                                                   std::vector<double>& parkDistance, std::vector<std::vector<MapPoint*>>& parkWalkPaths,
                                                   int i, int j, int k, double maxDistance){
    if (stopPoints.size() != shallPark.size()){
        throw std::invalid_argument("Whether to stop on each park must be specified");
    }

}
