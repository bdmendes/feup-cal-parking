#include <iostream>

#include "menu.h"
#include "../../util/util.h"
#include "../../algorithms/tsp.hpp"
#include "../../controller/parkselector.h"
#include "../../algorithms/shortestdistance.hpp"

using namespace util;

Menu::Menu(StreetMap& map) : UI(map){}

void Menu::show(){
    calculateRoute();
    std::cout << SEPARATOR
              << "Welcome, Driver\n"
              << SEPARATOR << std::endl;
    const std::vector<std::string> content = {
            "import map - import map from files",
            "analyse connectivity - check if the graph is connected",
            "choose start - choose the trip's starting point",
            "choose destination - choose the trip's destination point",
            "start works - mark works on public roads",
            "conclude works - conclude works on public roads",
            "add stop - add a stop/crossing point ",
            "remove stop - remove a stop/crossing point",
            "calculate_route - calculate the best route",
            "show map - show map and eventually the calculated route"
    };
    printOptions(content);

    for (;;) {
        std::string input = readCommand();
        if (input == EXIT) return;
        else if (validInput1Cmd1ArgFree(input, "import_map")) {
            importMap();
            break;
        }
        else if (validInput1Cmd1Arg(input,"analyse","connectivity")){
            //calculateConectivity(_map)
            break;
        }
        else if (validInput1Cmd1Arg(input,"choose","start")){
            //TODO
            break;
        }
        else if (validInput1Cmd1Arg(input,"choose","destination")){
            //TODO
            break;
        }
        else if (validInput1Cmd1Arg(input,"start","works")){
            //TODO
            break;
        }
        else if (validInput1Cmd1Arg(input,"conclude","works")){
            //TODO
            break;
        }
        else if (validInput1Cmd1Arg(input,"add","stop")){
            //TODO
            break;
        }
        else if (validInput1Cmd1Arg(input,"remove","stop")){
            //TODO
            break;
        }
        else if (validInput1Cmd(input,"calculate_route")){
            calculateRoute();
            break;
        }
        else if (validInput1Cmd1Arg(input,"show","map")){
            _map.showGraph();
            break;
        }
        else printError();
    }

    show();
}


void Menu::importMap() {
    std::string nodesXY("maps/porto/porto_strong_nodes_xy.txt");
    std::string nodesLL("maps/porto/porto_strong_nodes_latlng.txt");
    std::string edges("maps/porto/porto_strong_edges.txt");
    _map.readFromFile(nodesXY, nodesLL, edges);
}

void Menu::calculateRoute() {
    /* To test... */
    importMap();
    _source = _map.findNodeById(37);
    _destination = _map.findNodeById(124);
    auto p1 = _map.findNodeById(67);
    auto p2 = _map.findNodeById(89);
    _stopPoints.push_back(p1);
    _stopPoints.push_back(p2);
    _stopPointsShallPark.push_back(true);
    _stopPointsShallPark.push_back(true);
    _possibleTSP = true;

    if (_source == nullptr){
        std::cout << "Source node is not yet defined, try again\n";
        return;
    } else if (_destination == nullptr){
        std::cout << "Destination node is not yet defined, try again\n";
        return;
    } else if (_stopPoints.empty()){
        std::cout << "No stopping points were defined, try again\n";
        return;
    } else if (!_possibleTSP){
        std::cout << "We are not sure the graph is (strongly) connected, please analyse first\n";
        return;
    }

    std::cout << "\nCalculating route according to your preferences... Please wait" << std::endl;

    /* Assemble main path */
    auto path = getPathAfterParkReplacement(_map, _stopPoints, _source, _destination,
                                            _stopPointsShallPark, _iFactor, _kFactor, _jFactor, _maxParkWalk);
    auto walkPaths = getWalkPaths(_map, _stopPoints, path);
    double totalWalkDistance = 0;
    for (const auto& w: walkPaths){
        totalWalkDistance += distance(w);
    }

    /* Get best order */
    StreetMap* simplifiedMap = getSimplifiedMap(path);
    std::vector<Node<MapPoint>*> _bestOrderPath;
    tspNearestNeighbour(_source, path, _destination, _bestOrderPath);
    std::vector<Node<MapPoint>*> bestOrderPath;
    bestOrderPath.push_back(_source);
    for (const auto& s : _bestOrderPath) bestOrderPath.push_back(s);
    bestOrderPath.push_back(_destination);

    /* Assemble edges */
    std::vector<std::vector<Node<MapPoint>*>> describedPaths;
    double totalDistance = 0;
    for (int i = 0; i < bestOrderPath.size()-1; i++){
        dijkstra(bestOrderPath.at(i)->getElement(), _map);
        auto p = getDijkstraPath(_map, bestOrderPath.at(i)->getElement(), bestOrderPath.at(i+1)->getElement());
        totalDistance += distance(p);
        describedPaths.push_back(p);
    }

    /* Show statistics */
    std::cout << "\nRESULTS\n";
    std::cout << "Best found route (IDs): ";
    for (const auto& s : bestOrderPath) std::cout << s->getId() << ' ';
    std::cout << "\nCar distance: " << totalDistance << std::endl;
    std::cout << "Walk distance: " << totalWalkDistance << " (x2)" << std::endl;

    /* Show graph */
    _map.showGraph(describedPaths, walkPaths, 200);
}

StreetMap* Menu::getSimplifiedMap(std::vector<Node<MapPoint>*> path){
    auto* simplifiedMap = new StreetMap();
    for (const auto& p : path) simplifiedMap->addNode(p->getId(), p->getElement());
    _source = simplifiedMap->addNode(_source->getId(), _source->getElement());
    _destination = simplifiedMap->addNode(_destination->getId(), _destination->getElement());
    id_t edgeID = 1;
    path = simplifiedMap->getNodes();
    for (int i = 0; i < path.size(); i++){
        for (int j = 0; j < path.size(); j++){
            if (i == j) continue;
            dijkstra(path.at(i)->getElement(), _map);
            double dist = distance(getDijkstraPath(_map, path.at(i)->getElement(), path.at(j)->getElement()));
            simplifiedMap->addEdge(edgeID++, path.at(i), path.at(j), dist);
        }
    }
    return simplifiedMap;
}
