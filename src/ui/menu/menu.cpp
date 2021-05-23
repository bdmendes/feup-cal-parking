#include <iostream>

#include "menu.h"
#include "../../util/util.h"

using namespace util;

IntroMenu::IntroMenu(StreetMap& map) : UI(map){}

void IntroMenu::show(){
    std::cout << SEPARATOR
              << "Welcome\n"
              << SEPARATOR << std::endl;
    const std::vector<std::string> content = {
            "import map - import map from files",
            "edit map - remove or add nodes and vertices",
            "calculate trip - set starting, stop and arrival points",
            "export map - export map data to a file"
    };
    printOptions(content);

    for (;;) {
        std::string input = readCommand();
        if (input == EXIT) return;
        else if (validInput1Cmd1Arg(input, "import","map")) {
            importMap();
            break;
        }
        else if (validInput1Cmd1Arg(input,"edit","map")){
            //TODO
            break;
        }
        else if (validInput1Cmd1Arg(input,"calculate","trip")){
            //TODO
            break;
        }
        else if (validInput1Cmd1Arg(input,"export","map")){
            exportMap();
            break;
        }
        else printError();
    }

    show();
}


void IntroMenu::importMap() {
    std::string nodesXY("maps/porto/porto_strong_nodes_xy.txt");
    std::string nodesLL("maps/porto/porto_strong_nodes_latlng.txt");
    std::string edges("maps/porto/porto_strong_edges.txt");
    _map.readFromFile(nodesXY, nodesLL, edges);
}

void IntroMenu::exportMap() {
    std::cout << "\nEXPORT MAP\n" << SEPARATOR
              << "'data' folder path: ";
    std::string input = readCommand();
    if (input == BACK) return;
    std::cout << "\n" //<< graph.write() TODO
              << "\nPress enter to go back. ";
    std::getline(std::cin,input);
}
