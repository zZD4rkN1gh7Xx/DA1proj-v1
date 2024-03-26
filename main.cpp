//
// Created by Administrador on 20/03/2024.
//

#include <iostream>
#include "FileReader.h"
#include "WMSGraph.h"
#include "GraphTester.h"
#include "helpfunctions.h"
#include "Menu.h"

using namespace std;

int main(void)
{


    WMSGraph globalGraph;
    WMSGraph shadowGraph;

    FileReader::add_cities("../Project1DataSetSmall/Project1DataSetSmall/Cities_Madeira.csv",globalGraph);
    //cout << "Cities worked!" << endl;
    FileReader::add_cities("../Project1DataSetSmall/Project1DataSetSmall/Cities_Madeira.csv",shadowGraph);
    //cout << "Cities worked!" << endl;

    FileReader::add_reservoirs("../Project1DataSetSmall/Project1DataSetSmall/Reservoirs_Madeira.csv",globalGraph);
    //cout << "Reservoirs worked!" << endl;
    FileReader::add_reservoirs("../Project1DataSetSmall/Project1DataSetSmall/Reservoirs_Madeira.csv",shadowGraph);
    //cout << "Reservoirs worked!" << endl;

    FileReader::add_stations("../Project1DataSetSmall/Project1DataSetSmall/Stations_Madeira.csv",globalGraph);
    //cout << "Stations worked!" << endl;
    FileReader::add_stations("../Project1DataSetSmall/Project1DataSetSmall/Stations_Madeira.csv",shadowGraph);
    //cout << "Stations worked!" << endl;

    FileReader::add_pipes("../Project1DataSetSmall/Project1DataSetSmall/Pipes_Madeira.csv", globalGraph, shadowGraph);
    //cout << "Pipes worked!" << endl;

    std::vector<Agua> a = shadowGraph.get_all_sources("PoNTa dO Sol");

    for(auto b : a)
    {
        cout << b.get_code() << endl;
    }


    //Menu(globalGraph).MainMenu();



    return 0;
}