#ifndef MENU_H
#define MENU_H

#include "../ui.h"
#include "../../model/Graph/Graph.hpp"

class IntroMenu : public UI {
public:

    IntroMenu() = default;

    void show() override;

    void importMap();

    void exportMap();
};

#endif
