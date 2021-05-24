#include <algorithm>
#include <sstream>
#include "util.h"

bool util::isdigit(const std::string &str, bool acceptFloat) {
    int pointCount = 0;
    return !str.empty() && str.size() <= 9
    && std::all_of(str.begin(),str.end(), [&pointCount, acceptFloat](const char c){
        if (c == '.' && acceptFloat) return ++pointCount <= 1;
        return (bool) std::isdigit(c);
    });
}

bool util::contains(const std::string &str, const std::string &expected) {
    return str.find(expected) != std::string::npos;
}

void util::normalize(std::string &str) {
    bool forceLower = false;
    for (unsigned long i = 0; i < str.size(); ++i){
        if (str.at(i) == SPACE) forceLower = false;

        //strip unneeded spaces
        if (str.at(i) == SPACE && (i == 0 || (i < str.size() - 1 && str.at(i+1) == SPACE))){
            str.erase(str.begin() + i);
            i--;
            continue;
        }

        //ensure only first word char is uppercase
        if (forceLower || (std::isupper(str.at(i)) && i > 0 && std::isupper(str.at(i-1)))){
            str.at(i) = (char) std::tolower(str.at(i));
            forceLower = true;
            continue;
        }
    }
}

void util::lowercase(std::string &str) {
    std::transform(str.begin(),str.end(),str.begin(),[](unsigned char c){return std::tolower(c);});
}

std::string util::column(std::string str, bool large) {
    unsigned long colSize = large ? LARGE_COL_WIDTH : SMALL_COL_WIDTH;
    if (str.size() > colSize) str = str.substr(0, colSize - 4) + "... ";
    std::ostringstream ss;
    ss << std::setw((int)colSize) << std::left << str << SPACE;
    return ss.str();
}

std::string util::to_string(float n) {
    std::ostringstream ss;
    ss.precision(2);
    ss << std::fixed << n;
    return ss.str();
}

void util::clearScreen(){
    std::cout << '\n' << ANSI_CLEAR_SCREEN;
}

void util::print(const std::string& s, const int color){
    std::cout << ANSI_ANNOUNCE_COLOR << color << "m" << s << ANSI_RESET_CONSOLE;
}

std::vector<std::string> util::to_words(const std::string& input) {
    std::vector<std::string> words;
    std::stringstream ss(input);
    for (std::string current; ss >> current;) words.push_back(current);
    return words;
}

void util::uppercase(std::string &str) {
    std::transform(str.begin(),str.end(),str.begin(),[](unsigned char c){return std::toupper(c);});
}

void util::stripCarriageReturn(std::string& line){
    line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
}

