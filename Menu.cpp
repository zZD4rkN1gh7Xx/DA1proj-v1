//
// Created by jogos on 3/25/2024.
//


#include "Menu.h"
#include "solucao.h"

Menu::Menu(int regiao)
{
    this->regiao = regiao;
}

void Menu::DisplayMainMenu(void)
{
    cout<< "---------------------------" << " Water Supply Management System " << "---------------------------" << endl;
    cout<< "1 - Determine the maximum amount of water that can reach each city (2.1 and 2.2)" << endl;
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

            WMSGraph fazer;
            file_add(fazer, this->regiao);
            auto source = fazer.get_super_source();
            auto sink = fazer.get_super_sink();

            auto solve2 = edmondsKarp(fazer, *source, sink);
            vector<std::string> order;

            for (auto city : fazer.get_agua_city()) {
                order.push_back(city.first);
            }

            sort(order.begin(), order.end(), [&](const auto& first, const auto& second) {
                return fazer.get_city_by_code(first).get_id() < fazer.get_city_by_code(second).get_id();
            });

            int value = 0;

            for (auto cities : order) {
                if (cities != "CS_2") {
                    cout << cities << " - " << solve2[fazer.get_city_by_code(cities).get_id()] << endl;
                    value += solve2[fazer.get_city_by_code(cities).get_id()];
                }
            }

            cout << endl << value << endl;



            if(MenuToMain()) {
                MainMenu();
            }
            else
                break;


        }
        else if (ans == "2") {

            std::string cidade;
            cout << "What city do you choose?: ";
            cin >> cidade;
            cout << endl << endl;

            WMSGraph fazer;
            file_add(fazer, this->regiao);
            auto source = fazer.get_super_source();
            auto sink = fazer.get_super_sink();

            auto solve2 = edmondsKarp(fazer, *source, sink);
            vector<std::string> order;

            for (auto city : fazer.get_agua_city()) {
                order.push_back(city.first);
            }

            sort(order.begin(), order.end(), [&](const auto& first, const auto& second) {
                return fazer.get_city_by_code(first).get_id() < fazer.get_city_by_code(second).get_id();
            });

            int count = 0;

            for (auto cities : order) {
                if (cities == cidade) {
                    cout << cities << " - " << solve2[fazer.get_city_by_code(cities).get_id()] << endl;
                    count++;
                }
            }

            std::string ok;

            if (count == 0) {
                while (count == 0) {
                    cout << "That city doesn't exist! Try again?" << endl << "0 for no, type anything for yes: ";
                    cin >> ok;
                    cout << endl;
                    if (ok == "0")
                    {
                        count = -1;
                    }
                    else {
                        cout << "Which city do you want to see?: ";
                        cin >> cidade;
                        cout << endl;

                        for (auto cities: order) {
                            if (cities == cidade) {
                                cout << cities << " - " << solve2[fazer.get_city_by_code(cities).get_id()] << endl;
                                count++;
                            }
                        }
                    }
                }
            }

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
