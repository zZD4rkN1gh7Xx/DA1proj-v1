//
// Created by Administrador on 20/03/2024.
//

#include <iostream>
#include "FileReader.h"
#include "WMSGraph.h"
using namespace std;

int main(void)
{
    cout << "hi there :D" << endl;

    WMSGraph globalGraph;

    FileReader::add_cities("Project1DataSetSmall/Project1DataSetSmall/Cities_Madeira.csv", globalGraph);
    FileReader::add_reservoirs("Project1DataSetSmall/Project1DataSetSmall/Reservoirs_Madeira.csv", globalGraph);
    FileReader::add_stations("Project1DataSetSmall/Project1DataSetSmall/Stations_Madeira.csv", globalGraph);
    FileReader::add_pipes("Project1DataSetSmall/Project1DataSetSmall/Pipes_Madeira.csv", globalGraph);


    return 0;
}