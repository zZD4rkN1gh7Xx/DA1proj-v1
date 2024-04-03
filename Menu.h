#ifndef MENU_H
#define MENU_H

#include "WMSGraph.h"

class Menu {
private:
    WMSGraph Graph;
    WMSGraph Shadow;

public:
    Menu(WMSGraph Graph, WMSGraph Shadow);
    void displayMainMenu();
    void handleMenuSelection();
    bool promptReturnToMainMenu();
};

#endif // MENU_H

