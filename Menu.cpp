//
// Created by jogos on 3/25/2024.
//


#include "Menu.h"
#include "solucao.h"

Menu::Menu(void)
{
    this->regiao = -1;
}

void Menu::DisplayMainMenu(void)
{

    cout<< endl << "|" << " Water Supply Management System " << "|" << endl << endl;
    cout<< "1 - Determine the maximum amount of water that can reach each city (2.1)." << endl;
    cout<< "2 - Determine which cities don't get enough water (2.2)." << endl;
    cout<< "3 - Determine the maximum amount of water that can reach a specific city (2.1)." << endl;
    cout<< "4 - Delivery capacity changes when removing a chosen Water Reservoir (3.1)." << endl;
    cout<< "5 - Delivery capacity changes when removing each Pumping Station at a time (3.2)." << endl;
    cout<< "6 - Delivery capacity changes when removing each Pipe at a time (3.3)." << endl << endl;
}

void Menu::MainMenu(void) {
    string ans;
    bool ret;
    while(true) {
        cout << "Choose an option: ";
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

            std::ofstream out_file("../output.txt");
            out_file << "City code - Flow (m^3/s)" << endl << endl;

            for (auto cities : order) {
                if (cities != "CS_2") {
                    cout << cities << " - " << solve2[fazer.get_city_by_code(cities).get_id()] << endl;
                    out_file << cities << " - " << solve2[fazer.get_city_by_code(cities).get_id()] << endl;
                    value += solve2[fazer.get_city_by_code(cities).get_id()];
                }
            }
            out_file << endl << endl;
            out_file.close();

            cout << endl << "Total flow: " << value << endl;



            if(MenuToMain()) {
                DisplayMainMenu();
                MainMenu();
            }
            else
                break;


        }
        else if (ans == "2") {
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
                if (cities != "CS_2" && solve2[fazer.get_city_by_code(cities).get_id()] < fazer.get_city_by_code(cities).get_demand()) {
                    cout << cities << " - " << abs(solve2[fazer.get_city_by_code(cities).get_id()] - fazer.get_city_by_code(cities).get_demand()) << " deficit" << endl;
                    value += solve2[fazer.get_city_by_code(cities).get_id()];
                }
            }


            if(MenuToMain()) {
                DisplayMainMenu();
                MainMenu();
            }
            else
                break;
        }

        else if (ans == "3") {

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

            std::ofstream out_file("../output.txt");
            out_file << "City code - Flow (m^3/s)" << endl << endl;

            for (auto cities : order) {
                if (cities == cidade) {
                    cout << cities << " - " << solve2[fazer.get_city_by_code(cities).get_id()] << endl;
                    out_file << cities << " - " << solve2[fazer.get_city_by_code(cities).get_id()] << endl;;
                    count++;
                }
            }
            out_file << endl;
            out_file.close();

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
                DisplayMainMenu();
                MainMenu();
            }
            else
                break;
        }

        else if (ans == "4") {

            bool can = false;
            std::string code;

            while(can == false)
            {
                cout << "Which reservoir do you wish to remove?: ";
                cin >> code;
                cout << endl << endl;

                if (code[0] != 'R' || code[1] != '_') {
                    cout << "That is not a reservoir! Try again." << endl << endl;
                }
                else can = true;
            }

            reservoirs_affected_cities(regiao, code);


            if (MenuToMain()) {
                DisplayMainMenu();
                MainMenu();
            } else {
                break;
            }
        }

        else if (ans == "5") {

            std::string code;
            vector<std::string> not_affecting;


            WMSGraph fazer;
            file_add(fazer, this->regiao);
            auto source = fazer.get_super_source();
            auto sink = fazer.get_super_sink();

            auto expected = edmondsKarp(fazer, *source, sink);

            for (auto pumpings : fazer.get_pumping_stations()) {
                if (!pumping_stations_affected_cities(regiao, expected, pumpings.first)) {
                    not_affecting.push_back(pumpings.first);
                }
            }

            cout << endl;

            if (not_affecting.size() == 0) {
                cout << "There are no Pumping Stations that don't affect the network when removed." << endl << endl;
            }

            else {
                cout << "The Pumping Stations that can be removed without affecting the network are: "<< endl;
                for (auto no_deficit: not_affecting) {
                    cout << no_deficit << endl;
                }
            }

            if(MenuToMain()) {
                DisplayMainMenu();
                MainMenu();
            }
            else {
                break;
            }
        }

        if (ans == "6")
        {
            std::string code;
            vector<Pipe> not_affecting;


            WMSGraph fazer;
            file_add(fazer, this->regiao);
            auto source = fazer.get_super_source();
            auto sink = fazer.get_super_sink();

            auto expected = edmondsKarp(fazer, *source, sink);

            WMSGraph util;

            file_add(util, this->regiao);

            for (auto pipes : util.get_pipes()) {
                if (!pipes_affected_cities(regiao, expected, pipes.second)) {
                    not_affecting.push_back(pipes.second);
                }
            }

            cout << endl;

            if (not_affecting.size() == 0) {
                cout << "There are no Pipes that don't affect the network when removed." << endl << endl;
            }

            else {
                cout << "The Pipes that can be removed without affecting the network are: "<< endl;
                for (auto no_deficit: not_affecting) {
                    cout << no_deficit.get_code_A() << " - " << no_deficit.get_code_B() << endl;
                }
            }

            if(MenuToMain()) {
                DisplayMainMenu();
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

void Menu::Initializer(void) {
    bool can = false;
    int reg;
    while (!can) {
        cout << "What region will we be choosing?" << endl << "0 for Madeira(funciona) 1 for Portugal(duvidoso): ";
        cin >> reg;

        if (reg != 1 && reg != 0) {
            cout << endl << endl << "That is not one of the options." << endl << endl;
        }
        else {
            can = true;
        }
    }
    this->regiao = reg;
}
