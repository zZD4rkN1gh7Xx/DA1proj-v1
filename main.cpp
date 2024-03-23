//
// Created by Administrador on 20/03/2024.
//

#include <iostream>
#include "FileReader.h"
#include "WMSGraph.h"
#include "GraphTester.h"

using namespace std;

int main(void)
{

    /* Por alguma razão a única maneira de ler os ficheiros é a por o Working Directory
    para o DA1proj-v1 nas configurações de correr o programa */

    WMSGraph globalGraph;

    FileReader::add_cities(globalGraph);
    cout << "Cities worked!" << endl;
    FileReader::add_reservoirs(globalGraph);
    cout << "Reservoirs worked!" << endl;
    FileReader::add_stations(globalGraph);
    cout << "Stations worked!" << endl;
    FileReader::add_pipes(globalGraph);
    cout << "Pipes worked!" << endl;

    GraphTester(globalGraph).testPipes();
    GraphTester(globalGraph).testVertexes();
    GraphTester(globalGraph).testAguaPoints();

    return 0;
}