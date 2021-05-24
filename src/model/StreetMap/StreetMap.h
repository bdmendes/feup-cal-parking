#ifndef FEUP_CAL_PARKING_STREETMAP_H
#define FEUP_CAL_PARKING_STREETMAP_H

#include "../Graph/Graph.hpp"
#include "MapPoint.h"

#include "graphviewer.h"
#include <fstream>

class StreetMap : public Graph<MapPoint> {
public:
    StreetMap(unsigned int windowWidth, unsigned int windowHeight);
    void readFromFile(const std::string& nodesXYPath,
                      const std::string& nodesLatLongPath, const std::string& edgesPath);
    void showGraph();
    void showGraph(const std::vector<std::vector<Node<MapPoint> *>> &paths,
                   sf::Color edgeColor, sf::Color pointsColor, sf::Color parksColor,
                   sf::Color sourceColor, sf::Color targetColor, useconds_t colorDelay);
    Node<MapPoint> * addNode(id_t id, const MapPoint &element) override;
    Edge<MapPoint> * addEdge(id_t id, Node<MapPoint> *source, Node<MapPoint> *target, double weight) override;
    void removeNode(const MapPoint &element) override;
    void removeEdge(const MapPoint &source, const MapPoint &target) override;
private:
    void colorPath(const std::vector<Node<MapPoint> *> &path,
                   sf::Color edgeColor, sf::Color pointsColor,
                   sf::Color parksColor, useconds_t delay,
                   bool colorFirst, bool colorLast,
                   sf::Color sourceColor, sf::Color targetColor);
    void colorNode(id_t id, sf::Color color);
    void colorEdge(id_t id, sf::Color color);
    void retrieveDimensionLimits(std::ifstream &nodesXY);
    void readNodes(std::ifstream& nodesXY, std::ifstream& nodesLatLng);
    void readEdges(std::ifstream& edges);
    GraphViewer _gv;
    std::unordered_map<id_t, GraphViewer::Node*> _gvNodes;
    std::unordered_map<id_t, GraphViewer::Edge*> _gvEdges;
    unsigned _width;
    unsigned _height;
    double _minX = -3300, _minY = -3000, _maxX = 9500, _maxY = 3100;
};

#endif //FEUP_CAL_PARKING_STREETMAP_H
