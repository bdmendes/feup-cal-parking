#ifndef MENU_H
#define MENU_H

#include "../ui.h"
#include "../../model/Graph/Graph.hpp"
#include "../../model/StreetMap/StreetMap.h"

class Menu : public UI {
public:

    explicit Menu(StreetMap& map);

    void show() override;

    void defaultImportMap();

    void importMap(const std::string& input);
};

#endif
