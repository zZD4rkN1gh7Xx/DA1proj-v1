//
// Created by Administrador on 20/03/2024.
//

#include <iostream>
#include "FileReader.h"
#include "WMSGraph.h"
#include "GraphTester.h"
#include "helpfunctions.h"
#include "tarefas.h"
#include "Menu.h"

using namespace std;

int main(void)
{


    /*WMSGraph globalGraph;
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
    //cout << "Pipes worked!" << endl;*/

    WMSGraph teste;
    WMSGraph shadow_teste;

    WaterReservoir res = WaterReservoir("s", "b",  1, "R_2", 3);
    DeliverySite de = DeliverySite("Boooooooooooooooo", 1, "DL_1", 2, 1 );
    PumpingStation pu = PumpingStation(1, "P_2");

    teste.add_pumping_station(pu);
    teste.add_water_reservoir(res);
    teste.add_delivery_site(de);

    shadow_teste.add_pumping_station(pu);
    shadow_teste.add_water_reservoir(res);
    shadow_teste.add_delivery_site(de);

    Pipe pipe_1 = Pipe("R_2", "P_2", 5, 1);
    Pipe pipe_2 = Pipe("P_2", "DL_1", 5, 1);

    teste.add_pipe(pipe_1);
    teste.add_pipe(pipe_2);

    shadow_teste.add_pipe(pipe_1);
    shadow_teste.add_pipe(pipe_2);



    if(int a = edmonds_karp("Boooooooooooooooo","s", teste, shadow_teste))
    {
        std::cout << " we got to the functions" << std::endl;
    }

    return 0;
}