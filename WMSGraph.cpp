//
// Created by Administrador on 20/03/2024.
//

#include "WMSGraph.h"


void WMSGraph::add_delivery_site(DeliverySite& delivery_site)
{
    addVertex(delivery_site);
    this->aguapoints.insert(std::make_pair(delivery_site.get_code(), delivery_site));
}


void WMSGraph::add_pumping_station(PumpingStation& pumping_station)
{
    addVertex(pumping_station);
    this->aguapoints.insert(std::make_pair(pumping_station.get_code(), pumping_station));
}

void WMSGraph::add_water_reservoir(WaterReservoir& water_reservoir)
{
    addVertex(water_reservoir);
    this->aguapoints.insert(std::make_pair(water_reservoir.get_code(), water_reservoir));
}

void WMSGraph::remove_delivery_site(DeliverySite& delivery_site)
{
    removeVertex(delivery_site);

    auto it = aguapoints.find(delivery_site.get_delivery_site_code());

    if(it != aguapoints.end())
            aguapoints.erase(it);

}

void WMSGraph::remove_pumping_station(PumpingStation& pumping_station)
{
    removeVertex(pumping_station);

    auto it = aguapoints.find(pumping_station.get_code());

    if(it != aguapoints.end())
        aguapoints.erase(it);
}

void WMSGraph::remove_water_reservoir(WaterReservoir& water_reservoir)
{
    removeVertex(water_reservoir);

    auto it = aguapoints.find(water_reservoir.get_code());

    if(it != aguapoints.end())
        aguapoints.erase(it);
}

void WMSGraph::add_pipe(Pipe& pipe)
{
    addEdge(aguapoints[pipe.get_code_A()],aguapoints[pipe.get_code_B()], pipe);
}

void WMSGraph::remove_pipe(Pipe& pipe)
{
    removeEdge(aguapoints[pipe.get_code_A()], aguapoints[pipe.get_code_B()]);
}

std::unordered_map<std::string, Agua> WMSGraph::get_aguapoints(void) {
    return this->aguapoints;
}