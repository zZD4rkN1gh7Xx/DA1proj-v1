//
// Created by Administrador on 20/03/2024.
//

#include <iostream>
#include "WMSGraph.h"
#include "helpfunctions.h"
#include "Menu.h"

#include <algorithm>
#include <set>

using namespace std;


//NAO PODEMOS DAR SET AOS GETS QUE DA MERDA
//PRIMEIRO FAZEMOS GET E DPS SET
//COM UMA NOVA VARIAVEL (*calmly*)

int main(void)
{


    WMSGraph globalGraph;


    //FileReader::add_cities("../Project1DataSetSmall/Project1DataSetSmall/Cities_Madeira.csv",globalGraph);
    //../DA1proj-v1/Project1DataSetSmall/Project1DataSetSmall/Cities_Madeira.csv"
    //../DA1proj-v1/Project1LargeDataSet/Project1LargeDataSet/Cities.csv
    //cout << "Cities worked!" << endl;


    //FileReader::add_reservoirs("../Project1DataSetSmall/Project1DataSetSmall/Reservoirs_Madeira.csv",globalGraph);
    //../DA1proj-v1/Project1DataSetSmall/Project1DataSetSmall/Reservoirs_Madeira.csv
    //../DA1proj-v1/Project1LargeDataSet/Project1LargeDataSet/Reservoir.csv
    //cout << "Reservoirs worked!" << endl;


    //FileReader::add_stations("../Project1DataSetSmall/Project1DataSetSmall/Stations_Madeira.csv",globalGraph);
    //../DA1proj-v1/Project1DataSetSmall/Project1DataSetSmall/Stations_Madeira.csv
    //../DA1proj-v1/Project1LargeDataSet/Project1LargeDataSet/Stations.csv
    //cout << "Stations worked!" << endl;

    //FileReader::add_pipes("../Project1DataSetSmall/Project1DataSetSmall/Pipes_Madeira.csv", globalGraph);
    //../DA1proj-v1/Project1DataSetSmall/Project1DataSetSmall/Pipes_Madeira.csv
    //../DA1proj-v1/Project1LargeDataSet/Project1LargeDataSet/Pipes.csv
    //cout << "Pipes worked!" << endl;



    int reg;
    cout<<"What region will we be choosing?" << endl << "(0 for Madeira(funciona) 1 for Portugal(duvidoso)): ";
    cin>>reg;
    Menu menu(reg);
    menu.DisplayMainMenu();
    menu.MainMenu();






    return 0;
}
