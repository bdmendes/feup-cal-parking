#include <iostream>

#include "menu.h"
#include "../../util/util.h"

using namespace util;

Menu::Menu(StreetMap& map) : UI(map){}

void Menu::show(){
    std::cout << SEPARATOR
              << "Welcome\n"
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
            "calculate route - calculate the best route",
            "show map - show map and eventually the calculated route"
    };
    printOptions(content);

    for (;;) {
        std::string input = readCommand();
        if (input == EXIT) return;
        else if (validInput1Cmd1Arg(input, "import","map")) {
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
        else if (validInput1Cmd1Arg(input,"calculate","route")){
            //TODO
            break;
        }
        else if (validInput1Cmd1Arg(input,"show","map")){
            map.showGraph();
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
