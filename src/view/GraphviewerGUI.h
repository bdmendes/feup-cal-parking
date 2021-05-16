
#ifndef FEUP_CAL_PARKING_GRAPHVIEWERGUI_H
#define FEUP_CAL_PARKING_GRAPHVIEWERGUI_H

#include "../model/StreetMap/StreetMap.h"
#include "graphviewer.h"

class GraphviewerGUI {
public:
    GraphviewerGUI(const StreetMap &map, double width, double height);

    void createGV();

    void deleteGV();

    void show();

private:
    GraphViewer *_gv;
    StreetMap _map;
    size_t _width;
    size_t _height;
};


#endif //FEUP_CAL_PARKING_GRAPHVIEWERGUI_H
