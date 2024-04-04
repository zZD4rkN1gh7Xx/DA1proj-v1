//
// Created by jogos on 3/25/2024.
//


/*#include "Menu.h"
#include "tarefas_2.h"

Menu::Menu(WMSGraph Graph, WMSGraph Shadow)
{
    this->Graph = Graph;
    this->Shadow = Shadow;
}

void Menu::DisplayMainMenu(void)
{
    cout<< "---------------------------" << " Water Supply Management System " << "---------------------------" << endl;
    cout<< "1 - Determine the maximum amount of water that can reach each city (2.1)" << endl;
    cout<< "2 - Determine the maximum amount of water that can reach a specific city (2.1)" << endl;
    cout<< "3 - Test the Vertexes." << endl;
    cout<< "4 - Test the Aguapoints." << endl << endl;
}

void Menu::MainMenu(void) {
    string ans;
    bool ret;
    while(true) {
        cout << "Choose: ";
        cin>>ans;
        cout << endl;
        if (ans == "1") {

            int results = is_it_enough(Graph, Shadow);
            vector<std::string> order;

            for (auto city : Graph.get_agua_city()) {
                order.push_back(city.first);
            }

            sort(order.begin(), order.end(), [this](const auto& first, const auto& second) {
                return Graph.get_city_by_code(first).get_id() < Graph.get_city_by_code(second).get_id();
            });

            int value = 0;

            for (auto cities : order) {
                cout << "(" <<cities << ") " << Graph.get_city_by_code(cities).get_city() << " gets " << results[cities] << " m^3/s of water." << endl;
                value += results[cities];
            }

            cout << endl << value << endl;



            if(MenuToMain()) {
                MainMenu();
            }
            else
                break;


        }
        else if (ans == "2") {

            if(MenuToMain()) {
                MainMenu();
            }
            else
                break;
        }

        else if (ans == "3") {

            if(MenuToMain()) {
                MainMenu();
            }
            else {
                break;
            }
        }
        else if (ans == "4") {

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