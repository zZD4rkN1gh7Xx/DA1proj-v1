//
// Created by jogos on 3/25/2024.
//

#ifndef DA1PROJ_V1_MENU_H
#define DA1PROJ_V1_MENU_H


#include "WMSGraph.h"

class Menu {
    WMSGraph Graph;

    public:
        Menu(WMSGraph Graph);
        void MainMenu(void);
        bool MenuToMain(void);
};

#endif //DA1PROJ_V1_MENU_H
