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

class WMSGraph :public Graph<Agua>{

    private:
        std::unordered_map<std::string, Agua> aguapoints;
        std::unordered_map<std::string, DeliverySite> agua_cities;

    public:

        void add_delivery_site(DeliverySite& delivery_site);
        void add_pumping_station(PumpingStation& pumping_station);
        void add_water_reservoir(WaterReservoir& water_reservoir);
        void remove_delivery_site(DeliverySite& delivery_site);
        void remove_pumping_station(PumpingStation& pumping_station);
        void remove_water_reservoir(WaterReservoir& water_reservoir);
        void add_pipe(Pipe& pipe);
        void add_shadow_pipe(Pipe& pipe);
        void remove_pipe(Pipe& pipe);
        std::unordered_map<std::string, Agua> get_aguapoints(void);
        DeliverySite get_agua_city(std::string city);
};

template bool Graph<Agua>::addVertex(Agua &in);
template bool Graph<Agua>::removeVertex(Agua &in);

#endif //DAPROJ1_WMSGRAPH_H
