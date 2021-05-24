#ifndef MENU_H
#define MENU_H

#include "../ui.h"
#include "../../model/Graph/Graph.hpp"
#include "../../model/StreetMap/StreetMap.h"

class Menu : public UI {
public:
    explicit Menu(StreetMap& map);
    void show() override;
private:
    void calculateConnectivity(StreetMap &map, const std::vector<Node<MapPoint>*> &stopPoints, Node<MapPoint> *source);
    void defaultImportMap();
    void importMap(const std::string& input);
    void calculateRoute();
    StreetMap* getSimplifiedMap(std::vector<Node<MapPoint>*> path);
};

#endif
