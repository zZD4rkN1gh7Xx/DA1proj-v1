//
// Created by Administrador on 20/03/2024.
//

#include <iostream>
#include "FileReader.h"
#include "WMSGraph.h"
using namespace std;

int main(void)
{

    WMSGraph globalGraph;

    FileReader::add_cities(globalGraph);
    cout << "Cities added!" << endl;
    FileReader::add_reservoirs(globalGraph);
    cout << "Reservoirs added!" << endl;
    FileReader::add_stations(globalGraph);
    cout << "Stations added!" << endl;
    FileReader::add_pipes(globalGraph);
    cout << "Pipes added!" << endl;



    return 0;
}