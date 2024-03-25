//
// Created by Administrador on 20/03/2024.
//

#include <iostream>
#include "FileReader.h"
#include "WMSGraph.h"
#include "GraphTester.h"
#include "helpfunctions.h"

using namespace std;

int main(void)
{


    WMSGraph globalGraph;
    std::string testString = "aHaHahHHAAAAA";

    /*FileReader::add_cities("Project1DataSetSmall/Project1DataSetSmall/Cities_Madeira.csv",globalGraph);
    cout << "Cities worked!" << endl;
    FileReader::add_reservoirs("Project1DataSetSmall/Project1DataSetSmall/Reservoirs_Madeira.csv",globalGraph);
    cout << "Reservoirs worked!" << endl;
    FileReader::add_stations("Project1DataSetSmall/Project1DataSetSmall/Stations_Madeira.csv",globalGraph);
    cout << "Stations worked!" << endl;
    FileReader::add_pipes("Project1DataSetSmall/Project1DataSetSmall/Pipes_Madeira.csv", globalGraph);
    cout << "Pipes worked!" << endl;

    GraphTester(globalGraph).testPipes();
    GraphTester(globalGraph).testVertexes();
    GraphTester(globalGraph).testAguaPoints();*/

    std::cout << capitalizeFirstLetter(testString) << std::endl;


    return 0;
}