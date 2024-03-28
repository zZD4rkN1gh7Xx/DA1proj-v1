//
// Created by Administrador on 20/03/2024.
//

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

    public:

        void add_delivery_site(DeliverySite& delivery_site);
        void add_pumping_station(PumpingStation& pumping_station);
        void add_water_reservoir(WaterReservoir& water_reservoir);
        void remove_delivery_site(DeliverySite& delivery_site);
        void remove_pumping_station(PumpingStation& pumping_station);
        void remove_water_reservoir(WaterReservoir& water_reservoir);
        void add_pipe(Pipe& pipe);
        void add_shadow_pipe(Pipe& pipe);
        void remove_pipe(Pipe pipe);
        std::unordered_map<std::string, Agua> get_aguapoints(void);
        Agua get_agua_point(std::string agua_point);
        DeliverySite get_agua_city_name(std::string city);
        WaterReservoir get_agua_reservoir_name(std::string reservoir);
        DeliverySite get_agua_city_code(Agua agua);
        PumpingStation get_pumping_station_code(Agua agua);
        WaterReservoir get_water_reservoir_code(Agua agua);
        std::unordered_map<std::string, WaterReservoir> get_agua_reservoir();
        void set_all_unvisited(const vector<Vertex<Agua> * >& all_agua); // auxiliar function self-explanatory
        std::vector<Agua> get_all_sources(std::string sink); // auxiliar function
        void reset_shadow_capacities(void);
};

template bool Graph<Agua>::addVertex(Agua &in);
template bool Graph<Agua>::removeVertex(Agua &in);

#endif //DAPROJ1_WMSGRAPH_H
