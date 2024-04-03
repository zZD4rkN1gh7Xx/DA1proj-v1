

#include "Menu.h"
#include "GraphTester.h"
#include "tarefas.h"
#include <iostream>

Menu::Menu(WMSGraph Graph, WMSGraph Shadow) {
    this->Graph = Graph;
    this->Shadow = Shadow;
}

void Menu::displayMainMenu() {
    std::cout << "---------------------- Water Supply Management System ----------------------" << std::endl;
    std::cout << "1 - Determine the maximum amount of water that can reach each city." << std::endl;
    std::cout << "2 - Test Pipe Removal." << std::endl;
    std::cout << "3 - Test the Vertexes." << std::endl;
    std::cout << "4 - Test the Aguapoints." << std::endl << std::endl;
}




void Menu::handleMenuSelection() {
    while (true) {
        std::string choice;
        std::cout << "Choose an option (0 to exit): ";
        std::cin >> choice;

        if (choice == "0") {
            break;
        } else if (choice >= "1" && choice <= "4") {
            WMSGraph temp;
            temp = Graph;
            switch (choice[0]) {
                case '1':
                    for (auto c: temp.get_agua_city()) {
                        int edmonds = full_edmonds_karp(c.first, temp, Shadow);
                        temp = Graph;
                        cout << "The city of " << c.second.get_city() << " can get at most " << edmonds
                             << " m^3/s of water." << endl;
                    }
                    if (promptReturnToMainMenu()) {
                        displayMainMenu();
                        handleMenuSelection();
                    }
                    break;
                case '2':
                    GraphTester(Graph).testPipesRemoval();
                    if (promptReturnToMainMenu()) {
                        displayMainMenu();
                        handleMenuSelection();
                    }
                    break;
                case '3':
                    GraphTester(Graph).testVertexes();
                    if (promptReturnToMainMenu()) {
                        displayMainMenu();
                        handleMenuSelection();
                    }
                    break;
                case '4':
                    GraphTester(Graph).testAguaPoints();
                    if (promptReturnToMainMenu()) {
                        displayMainMenu();
                        handleMenuSelection();
                    }
                    break;
            }
            if (!promptReturnToMainMenu()) {
                break;
            }
        } else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}

bool Menu::promptReturnToMainMenu() {
    std::string ans;
    std::cout << std::endl << "Return to the Main Menu? (Type any character for yes, 0 for no): ";
    std::cin >> ans;
    return ans != "0";
}
