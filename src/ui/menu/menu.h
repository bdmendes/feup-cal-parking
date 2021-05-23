#ifndef MENU_H
#define MENU_H

#include "../ui.h"
#include "../../model/Graph/Graph.hpp"
#include "../../model/StreetMap/StreetMap.h"

class IntroMenu : public UI {
public:

    explicit IntroMenu(StreetMap& map);

    void show() override;

    void importMap();

    void exportMap();
};

#endif
