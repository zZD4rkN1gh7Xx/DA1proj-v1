//
// Created by Administrador on 20/03/2024.
//

/**

    *@file WMSGraph.h
    *@brief Header file for the WMSGraph class and an extention of graph.h
*/

#ifndef DAPROJ1_WMSGRAPH_H
#define DAPROJ1_WMSGRAPH_H

#include "Graph.h"
#include "deliverySites.h"
#include "pumpingStations.h"
#include "waterReservoir.h"
#include "Pipes.h"
#include "agua.h"
#include <unordered_map>
#include "helpfunctions.h"
#include <queue>

class WMSGraph :public Graph<Agua>{

    private:

        std::unordered_map<std::string, Agua> aguapoints; // unordered map co tudos os vertexes do grapho e chave o seu codigo
        std::unordered_map<std::string, DeliverySite> agua_cities_name; // unordered map com os vertexes que sao delivery sites do grapho e chave o seu nome
        std::unordered_map<std::string, DeliverySite> agua_cities_code; // unordered map com os vertexes que sao delivery sites  do grapho e chave o seu codigo
        std::unordered_map<std::string, PumpingStation> agua_pumping_stations_code; // unordered map com as pumping stations do grapho e chave o seu codigo
        std::unordered_map<std::string, WaterReservoir> agua_water_reservoir_code; // unordered map com os water reservoirs do grapho e chave o seu codigo
        std::unordered_map<std::string, WaterReservoir> agua_water_reservoir_name; // unordered map com os water reservoirs do grapho e chave o seu nome
        std::unordered_map<int, PumpingStation> agua_pumping_stations; // unordered map com as pumping stations do grapho e chave o seu id
        std::unordered_map<int, Pipe> agua_pipes;

    public:

        WMSGraph();
        WMSGraph(WMSGraph &graph);
        void add_delivery_site(DeliverySite& delivery_site);
        void add_pumping_station(PumpingStation& pumping_station);
        void add_water_reservoir(WaterReservoir& water_reservoir);
        void add_pipe(Pipe& pipe);
        void remove_pipe(Pipe pipe);
        Agua get_agua_point(std::string agua_point);
        DeliverySite get_city_by_code(std::string code);
        PumpingStation get_pumping_station_code(Agua agua);
        std::unordered_map<std::string, PumpingStation> get_pumping_stations();
        WaterReservoir get_water_reservoir_code(std::string code);
        std::unordered_map<std::string, WaterReservoir> get_agua_reservoir();
        Pipe get_pipe_id(int id);
        std::unordered_map<int, Pipe> get_pipes(void);
        std::unordered_map<std::string, DeliverySite> get_agua_city();
        DeliverySite get_city_id(int id);
        Vertex<Agua> * get_super_sink();
        Vertex<Agua> * get_super_source();

};

template bool Graph<Agua>::addVertex(Agua &in);
template bool Graph<Agua>::removeVertex(Agua &in);

#endif //DAPROJ1_WMSGRAPH_H
