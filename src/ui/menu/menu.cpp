#include <iostream>

#include "menu.h"
#include "../../util/util.h"

using namespace util;

void IntroMenu::show() {
    std::cout << SEPARATOR
              << "Welcome\n"
              << SEPARATOR << std::endl;
    const std::vector<std::string> content = {
            "import map - import map from files",
            "edit map - remove or add nodes and vertices",
            "calculate trip - set starting, stop and arrival points"
    };
    printOptions(content);

    /*for (;;) {
        std::string input = readCommand();
        if (input == EXIT) return;
        else if (validInput1Cmd1Arg(input, "manage","store")) {
            LoginMenu(_store).show();
            break;
        }
        else if (validInput1Cmd1Arg(input,"import","data")){
            importData();
            break;
        }
        else if (validInput1Cmd1Arg(input,"export","data")){
            exportData();
            break;
        }
        else printError();
    }*/

    //show();
}


void IntroMenu::importMap() {
    std::cout << "\nIMPORT MAP\n"
    << SEPARATOR << "'data' folder path: ";
    std::string input = readCommand();
    if (input == BACK) return;
    std::cout << "\n" // << graph.read() TODO
    << "\nPress enter to go back. ";
    std::getline(std::cin,input);
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
