//
// Created by Administrador on 20/03/2024.
//

#include <iostream>
#include "FileReader.h"
#include "WMSGraph.h"
#include "GraphTester.h"
#include "helpfunctions.h"
#include "tarefas_2.h"


#include <algorithm>
#include <set>

using namespace std;


//NAO PODEMOS DAR SET AOS GETS QUE DA MERDA
//PRIMEIRO FAZEMOS GET E DPS SET
//COM UMA NOVA VARIAVEL (*calmly*)

int main(void)
{


    WMSGraph globalGraph;
    WMSGraph shadowGraph;

    FileReader::add_cities("../Project1DataSetSmall/Project1DataSetSmall/Cities_Madeira.csv",globalGraph);
    //../DA1proj-v1/Project1DataSetSmall/Project1DataSetSmall/Cities_Madeira.csv"
    //../DA1proj-v1/Project1LargeDataSet/Project1LargeDataSet/Cities.csv
    //cout << "Cities worked!" << endl;
    FileReader::add_cities("../Project1DataSetSmall/Project1DataSetSmall/Cities_Madeira.csv",shadowGraph);
    //cout << "Cities worked!" << endl;

    FileReader::add_reservoirs("../Project1DataSetSmall/Project1DataSetSmall/Reservoirs_Madeira.csv",globalGraph);
    //../DA1proj-v1/Project1DataSetSmall/Project1DataSetSmall/Reservoirs_Madeira.csv
    //../DA1proj-v1/Project1LargeDataSet/Project1LargeDataSet/Reservoir.csv
    //cout << "Reservoirs worked!" << endl;
    FileReader::add_reservoirs("../Project1DataSetSmall/Project1DataSetSmall/Reservoirs_Madeira.csv",shadowGraph);
    //cout << "Reservoirs worked!" << endl;

    FileReader::add_stations("../Project1DataSetSmall/Project1DataSetSmall/Stations_Madeira.csv",globalGraph);
    //../DA1proj-v1/Project1DataSetSmall/Project1DataSetSmall/Stations_Madeira.csv
    //../DA1proj-v1/Project1LargeDataSet/Project1LargeDataSet/Stations.csv
    //cout << "Stations worked!" << endl;
    FileReader::add_stations("../Project1DataSetSmall/Project1DataSetSmall/Stations_Madeira.csv",shadowGraph);
    //cout << "Stations worked!" << endl;

    FileReader::add_pipes("../Project1DataSetSmall/Project1DataSetSmall/Pipes_Madeira.csv", globalGraph, shadowGraph);
    //../DA1proj-v1/Project1DataSetSmall/Project1DataSetSmall/Pipes_Madeira.csv
    //../DA1proj-v1/Project1LargeDataSet/Project1LargeDataSet/Pipes.csv
    //cout << "Pipes worked!" << endl;


    WMSGraph teste;
    WMSGraph shadow_teste;

    WaterReservoir res = WaterReservoir("s", "b",  1, "R_2", 99);
    DeliverySite de = DeliverySite("Boooooooooooooooo", 1, "C_1", 2, 1 );
    PumpingStation pu = PumpingStation(1, "P_2");
    PumpingStation pu2 = PumpingStation(2, "P_5");
    PumpingStation pu3 = PumpingStation(3, "P_ciclo1");
    PumpingStation pu4 = PumpingStation(4, "P_ciclo2");
    DeliverySite de2 = DeliverySite("T", 2, "C_2", 10, 10);


    teste.add_pumping_station(pu);
    teste.add_water_reservoir(res);
    teste.add_delivery_site(de);
    teste.add_pumping_station(pu2);
    teste.add_pumping_station(pu3);
    teste.add_pumping_station(pu4);
    teste.add_delivery_site(de2);

    shadow_teste.add_pumping_station(pu);
    shadow_teste.add_water_reservoir(res);
    shadow_teste.add_delivery_site(de);
    shadow_teste.add_pumping_station(pu2);
    shadow_teste.add_delivery_site(de2);
    shadow_teste.add_pumping_station(pu3);
    shadow_teste.add_pumping_station(pu4);



    Pipe pipe_1 = Pipe("R_2", "P_2", 10, 1, 1);
    Pipe pipe_2 = Pipe("P_2", "C_1", 5, 1,2);
    Pipe pipe_3 = Pipe("P_2", "P_5", 5, 1,3);
    Pipe pipe_4 = Pipe("P_5", "C_2", 5, 1, 4);
    Pipe pipe_5 = Pipe("P_5","P_ciclo1", 5,1,5);
    Pipe pipe_6 = Pipe("P_ciclo1","P_ciclo2", 5,1,6);
    Pipe pipe_7 = Pipe("P_ciclo2","P_5", 5,1,7);



    teste.add_pipe(pipe_1);
    teste.add_pipe(pipe_2);
    teste.add_pipe(pipe_3);
    teste.add_pipe(pipe_4);
    teste.add_pipe(pipe_5);
    teste.add_pipe(pipe_6);
    teste.add_pipe(pipe_7);

    shadow_teste.add_shadow_pipe(pipe_1);
    shadow_teste.add_shadow_pipe(pipe_2);
    shadow_teste.add_shadow_pipe(pipe_3);
    shadow_teste.add_shadow_pipe(pipe_4);
    shadow_teste.add_shadow_pipe(pipe_5);
    shadow_teste.add_shadow_pipe(pipe_6);
    shadow_teste.add_shadow_pipe(pipe_7);

    WMSGraph dummy = globalGraph;
    WMSGraph shadowDummy = shadowGraph;

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
    shadowGraph.add_delivery_site(super_del);

    for (auto sink: globalGraph.get_agua_city()) // inicaliazdor das cidades que cada reservatoio chega
    {
        if (sink.second != super_del) {
            count++;
            auto pipe = Pipe(sink.second.get_code(), "CS_2", sink.second.get_demand(), 1,globalGraph.get_pipes().size() + count);

            globalGraph.add_pipe(pipe);
        }
    }


    cout << edmondsKarp(globalGraph, *globalGraph.findVertex(super_res), globalGraph.findVertex(super_del));







    return 0;
}
