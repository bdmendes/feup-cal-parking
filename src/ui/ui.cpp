#include <iostream>

#include "ui.h"
#include "../util/util.h"

using namespace util;

const char* UI::BACK = "back";
const char* UI::EXIT = "exit";

UI::UI(StreetMap& map) : _map(map) {}

std::string UI::readCommand(bool lowCase) {
    std::string input;
    while (input.empty()) std::getline(std::cin, input);
    normalize(input);
    if (lowCase) util::lowercase(input);
    return input;
}

bool UI::validInput1Cmd(const std::string& input, const std::string &cmd) {
    std::vector<std::string> words = to_words(input);
    return words.size() == 1 && words.at(0) == cmd;
}

bool UI::validInput1Cmd1ArgDigit(const std::string& input, const std::string &cmd, bool acceptFloat) {
    std::vector<std::string> words = to_words(input);
    return words.size() == 2 && words.at(0) == cmd && isdigit(words.at(1),acceptFloat);
}

bool UI::validInput1Cmd1Arg(const std::string& input, const std::string &cmd, const std::string &arg) {
    std::vector<std::string> words = to_words(input);
    return words.size() == 2 && words.at(0) == cmd && words.at(1) == arg;
}

bool UI::validInput1Cmd2ArgsDigit(const std::string &input, const std::string &cmd, bool acceptFloatArg2) {
    std::vector<std::string> words = to_words(input);
    return words.size() == 3 && words.at(0) == cmd
           && isdigit(words.at(1)) && isdigit(words.at(2),acceptFloatArg2);
}

void UI::printOptions(const std::vector<std::string> &options, const std::string& message) {
    std::cout << message << '\n';
    for (const auto& o: options) std::cout << "-> " << o << '\n';
    std::cout << '\n';
}

void UI::printError() {
    std::cout << "Unrecognized command. Try again.\n";
}


