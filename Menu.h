//
// Created by jogos on 3/25/2024.
//

/**

*@file Menu.h
*@brief Header file for the Menu class
*/

#ifndef DA1PROJ_V1_MENU_H
#define DA1PROJ_V1_MENU_H


#include "WMSGraph.h"

class Menu {
    int regiao;

    public:

        Menu();
        void Initializer(void);
        void DisplayMainMenu(void);
        void MainMenu(void);
        bool MenuToMain(void);
};

#endif //DA1PROJ_V1_MENU_H
