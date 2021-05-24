#include <iostream>
#include "model/Graph/Graph.hpp"
#include "ui/menu/menu.h"
#include "model/StreetMap/StreetMap.h"
#include "algorithms/search.hpp"

int main() {
    std::srand(std::time(nullptr));
    StreetMap map(1900, 1000);
    Menu introMenu(map);
    introMenu.show();
}
