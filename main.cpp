//
// Created by Administrador on 20/03/2024.
//

#include <iostream>
#include "FileReader.h"
#include "WMSGraph.h"
#include "GraphTester.h"
#include "helpfunctions.h"
#include "soluçao.h"

#include <algorithm>
#include <set>

using namespace std;


//NAO PODEMOS DAR SET AOS GETS QUE DA MERDA
//PRIMEIRO FAZEMOS GET E DPS SET
//COM UMA NOVA VARIAVEL (*calmly*)

int main(void)
{


    WMSGraph globalGraph;


    FileReader::add_cities("../DA1proj-v1/Project1DataSetSmall/Project1DataSetSmall/Cities_Madeira.csv",globalGraph);
    //../DA1proj-v1/Project1DataSetSmall/Project1DataSetSmall/Cities_Madeira.csv"
    //../DA1proj-v1/Project1LargeDataSet/Project1LargeDataSet/Cities.csv
    //cout << "Cities worked!" << endl;


    FileReader::add_reservoirs("../DA1proj-v1/Project1DataSetSmall/Project1DataSetSmall/Reservoirs_Madeira.csv",globalGraph);
    //../DA1proj-v1/Project1DataSetSmall/Project1DataSetSmall/Reservoirs_Madeira.csv
    //../DA1proj-v1/Project1LargeDataSet/Project1LargeDataSet/Reservoir.csv
    //cout << "Reservoirs worked!" << endl;


    FileReader::add_stations("../DA1proj-v1/Project1DataSetSmall/Project1DataSetSmall/Stations_Madeira.csv",globalGraph);
    //../DA1proj-v1/Project1DataSetSmall/Project1DataSetSmall/Stations_Madeira.csv
    //../DA1proj-v1/Project1LargeDataSet/Project1LargeDataSet/Stations.csv
    //cout << "Stations worked!" << endl;

    FileReader::add_pipes("../DA1proj-v1/Project1DataSetSmall/Project1DataSetSmall/Pipes_Madeira.csv", globalGraph);
    //../DA1proj-v1/Project1DataSetSmall/Project1DataSetSmall/Pipes_Madeira.csv
    //../DA1proj-v1/Project1LargeDataSet/Project1LargeDataSet/Pipes.csv
    //cout << "Pipes worked!" << endl;


    int count = 0;

    WaterReservoir super_res = WaterReservoir("super", "RS_2", globalGraph.get_agua_reservoir().size() + 1, "RS_2", 0);
    DeliverySite super_del = DeliverySite("City Super", globalGraph.get_agua_city().size() + 1, "CS_2", 0, 0);

    for (auto reservoir: globalGraph.get_agua_reservoir()) // inicaliazdor das cidades que cada reservatoio chega
    {
        super_res.set_max_delivery(super_res.get_max_delivery() + reservoir.second.get_max_delivery());
    }

    globalGraph.add_water_reservoir(super_res);

    for (auto reservoir: globalGraph.get_agua_reservoir()) // inicaliazdor das cidades que cada reservatoio chega
    {
        if (reservoir.second != super_res) {
            count++;
            Pipe pipe;
            pipe = Pipe("RS_2", reservoir.second.get_code(), reservoir.second.get_max_delivery(), 1,globalGraph.get_pipes().size() + count);

            globalGraph.add_pipe(pipe);
        }
    }

    count = 0;

    for (auto sink: globalGraph.get_agua_city()) {
        super_del.set_demand(super_del.get_demand() + sink.second.get_demand());
    }

    globalGraph.add_delivery_site(super_del);


    for (auto sink: globalGraph.get_agua_city()) // inicaliazdor das cidades que cada reservatoio chega
    {
        if (sink.second != super_del) {
            count++;
            auto pipe = Pipe(sink.second.get_code(), "CS_2", sink.second.get_demand(), 1,globalGraph.get_pipes().size() + count);

            globalGraph.add_pipe(pipe);
        }
    }


    pumping_stations_affected_cities(globalGraph);





    return 0;
}
