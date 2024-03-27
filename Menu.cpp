//
// Created by jogos on 3/25/2024.
//


#include "Menu.h"
#include "GraphTester.h"
#include "tarefas.h"

Menu::Menu(WMSGraph Graph, WMSGraph Shadow)
{
    this->Graph = Graph;
    this->Shadow = Shadow;
}

int Menu::MainMenu(void)
{
    cout<< "---------------------------" << " Water Supply Management System " << "---------------------------" << endl;
    cout<< "5 - City delivery tests (2.1 / 2.2 / 2.3)" << endl;
    cout<< "1 - Test the Pipes." << endl;
    cout<< "2 - Test Pipe Removal." << endl;
    cout<< "3 - Test the Vertexes." << endl;
    cout<< "4 - Test the Aguapoints." << endl << endl;

    string opc;
    while(true) {
        cout << "Choose: ";
        cin>>opc;
        if (opc == "5") {
            if (WaterDelivMenu() == 0)
                return 0;
        }
        if (opc == "1") {
            GraphTester(Graph).testPipes();
            if(MenuToMain()) {
                MainMenu();
            }
            else
                return 0;


        }
        else if (opc == "2") {
            GraphTester(Graph).testPipesRemoval();
            if(MenuToMain()) {
                MainMenu();
            }
            else
                return 0;
        }

        else if (opc == "3") {
            GraphTester(Graph).testVertexes();
            if(MenuToMain()) {
                MainMenu();
            }
            else {
                return 0;
            }
        }
        else if (opc == "4") {
            GraphTester(Graph).testAguaPoints();
            if(MenuToMain()) {
                MainMenu();
            }
            else {
                return 0;
            }
        }
        else if (opc == "0") break;
        else {
            cout << "You typed something that is not one of the options." << endl
                 << "Do you want to try again? (any character for yes, type 0 for no)" << endl;
            cin >> opc;
            if (opc == "0") {
                return 0;
            }
            continue;
        }
        break;
    }
}

bool Menu::MenuToMain(void)
{
    string ret;
    cout << endl << "Want to return to the Main Menu? (any character for yes, type 0 for no)" << endl;
    cin >> ret;
    if (ret == "0") return false;
    else {
        return true;
    }

}

int Menu::WaterDelivMenu(void)
{
    cout<< endl << endl << "---------------------------" << " Water Delivery Tests " << "---------------------------" << endl;
    cout<< "1 - Max water that can reach specific city" << endl;
    cout<< "2 - Max water that can reach each city" << endl;

    string ans;
    string city;
    bool search = true;
    bool found = false;

    while (true) {
        cout << "Choose: ";
        cin >> ans;
        search = true;
        while(search == true) {
            if (ans == "1") {
                int result;
                cout << endl << endl << "Choose a city: ";
                cin >> city;
                while (search == true) {
                    for (auto c: Graph.get_agua_cities()) {
                        if (capitalizeFirstLetter(c.first) == capitalizeFirstLetter(city)) {
                            result = full_edmonds_karp(city, Graph, Shadow);
                            cout << endl << endl << "The city of " << c.first << " (" << c.second.get_code()
                                 << ") can get at most " << result << "m^3/s of water." << endl;
                            found = true;
                        }
                    }
                    if (found == false)
                        cout << endl << endl << "The city you are looking for doesn't exist." << endl;
                    if (MenuToMain()) {
                        MainMenu();
                    } else {
                        search = false;
                        return 0;
                    }
                }
            }
            else {
                cout << endl << "You typed something that is not one of the options." << endl
                     << "Do you want to try again? (any character for yes, type 0 for no)" << endl;
                cin >> ans;
                if (ans == "0") {
                    return 0;
                }
                search = false;
                continue;
            }
        }
        break;
        }

    return 0;
    }

