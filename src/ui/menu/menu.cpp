#include <iostream>
#include <sstream>
#include <stdexcept>

#include "menu.h"
#include "../../util/util.h"
#include "../../controller/connectivity.h"

using namespace util;

Menu::Menu(StreetMap& map) : UI(map){}

void Menu::show(){
    std::cout << SEPARATOR
              << "Welcome\n"
              << SEPARATOR << std::endl;
    const std::vector<std::string> content = {
            "import_map - import map from files. Usage: import_map [pathNodesXY,pathNodesLL,pathEdges]",
            "analyse_connectivity - check if the graph is connected",
            "choose_start - choose the trip's starting point. Usage: choose_start <nodeId>",
            "choose_destination - choose the trip's destination point",
            "start_works - mark works on public roads",
            "conclude_works - conclude works on public roads",
            "add_stop - add a stop/crossing point ",
            "remove_stop - remove a stop/crossing point",
            "calculate_route - calculate the best route",
            "show_map - show map and eventually the calculated route"
    };
    printOptions(content);

        for (;;) {
            try {
                std::string input = readCommand();
                if (input == EXIT) return;
                else if (validInput1Cmd1ArgFree(input, "import_map")) {
                    std::vector<std::string> words = to_words(input);
                    if (words.size() == 1) defaultImportMap();
                    else importMap(words.at(1));
                    break;
                } else if (validInput1Cmd(input, "analyse_connectivity")) {
                    if(_source == nullptr || _destination == nullptr || stopPoints.empty())
                        throw std::logic_error("Can't calculate the connectivity of the graph. Choose your source and destination points first.\n");
                    else calculateConnectivity(_map, stopPoints, _source);
                    break;
                } else if (validInput1Cmd1ArgDigits(input, "choose_start")) {
                    unsigned long nodeId = std::stoul(to_words(input).at(1)) - 1;
                    if (_map.findNodeById(nodeId) == nullptr)
                        throw std::logic_error("Node not found");
                    else _source = _map.findNodeById(nodeId);
                    break;
                } else if (validInput1Cmd1ArgDigits(input, "choose_destination")) {
                    unsigned long nodeId = std::stoul(to_words(input).at(1)) - 1;
                    if (_map.findNodeById(nodeId) == nullptr)
                        throw std::logic_error("Node not found");
                    else _destination = _map.findNodeById(nodeId);
                    break;
                } else if (validInput1Cmd1Arg(input, "start", "works")) {
                    //TODO
                    break;
                } else if (validInput1Cmd1Arg(input, "conclude", "works")) {
                    //TODO
                    break;
                } else if (validInput1Cmd1Arg(input, "add", "stop")) {
                    //TODO
                    break;
                } else if (validInput1Cmd1Arg(input, "remove", "stop")) {
                    //TODO
                    break;
                } else if (validInput1Cmd1Arg(input, "calculate", "route")) {
                    //TODO
                    break;
                } else if (validInput1Cmd1Arg(input, "show", "map")) {
                    _map.showGraph();
                    break;
                } else printError();
            }
            catch (std::exception &exception) {
                std::cout << exception.what() << '\n';
            }
        }
    show();
}


void Menu::defaultImportMap() {
    std::string nodesXY("maps/porto/porto_strong_nodes_xy.txt");
    std::string nodesLL("maps/porto/porto_strong_nodes_latlng.txt");
    std::string edges("maps/porto/porto_strong_edges.txt");
    _map.readFromFile(nodesXY, nodesLL, edges);
}

void Menu::importMap(const std::string& input){
    std::string nodesXY;
    std::string nodesLL;
    std::string edges;
    std::istringstream ss(input);
    std::string sep = ",";
    ss >> nodesXY >> sep >> nodesLL >> sep >> edges;
    _map.readFromFile(nodesXY, nodesLL, edges);
}

void Menu::calculateConnectivity(StreetMap &map, const std::vector<Node<MapPoint>*> &stopPoints, Node<MapPoint> *source){
    if (isStronglyConnected(_map)) std::cout << "The graph is strongly connected\n";
    else if (isConnected(_map, stopPoints, source) ) std::cout << "The graph is connected\n";
}
