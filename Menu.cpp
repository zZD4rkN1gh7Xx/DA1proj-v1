//
// Created by jogos on 3/25/2024.
//
/*

#include "Menu.h"
#include "GraphTester.h"

Menu::Menu(WMSGraph Graph)
{
    this->Graph = Graph;
}

void Menu::MainMenu(void)
{
    cout<< "---------------------------" << " Water Supply Management System " << "---------------------------" << endl;
    cout<< "1 - Test the Pipes." << endl;
    cout<< "2 - Test Pipe Removal." << endl;
    cout<< "3 - Test the Vertexes." << endl;
    cout<< "4 - Test the Aguapoints." << endl << endl;

    string ans;
    bool ret;
    while(true) {
        cout << "Choose: ";
        cin>>ans;
        if (ans == "1") {
            GraphTester(Graph).testPipes();
            if(MenuToMain()) {
                MainMenu();
            }
            else
                break;


        }
        else if (ans == "2") {
            GraphTester(Graph).testPipesRemoval();
            if(MenuToMain()) {
                MainMenu();
            }
            else
                break;
        }

        else if (ans == "3") {
            GraphTester(Graph).testVertexes();
            if(MenuToMain()) {
                MainMenu();
            }
            else {
                break;
            }
        }
        else if (ans == "4") {
            GraphTester(Graph).testAguaPoints();
            if(MenuToMain()) {
                MainMenu();
            }
            else {
                break;
            }
        }
        else if (ans == "0") break;
        else {
            cout << "You typed something that is not one of the options." << endl
                 << "Do you want to try again? (any character for yes, type 0 for no)" << endl;
            cin >> ans;
            if (ans == "0") break;
            continue;
        }
        break;
    }
}

bool Menu::MenuToMain(void)
{
    string ans;
    cout << endl << "Want to return to the Main Menu? (any character for yes, type 0 for no)" << endl;
    cin >> ans;
    if (ans == "0") return false;
    else {
        return true;
    }

}
 */