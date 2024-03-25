//
// Created by Administrador on 20/03/2024.
//

#include "WMSGraph.h"


void WMSGraph::add_delivery_site(DeliverySite& delivery_site)
{
    addVertex(delivery_site);
    this->aguapoints.insert(std::make_pair(delivery_site.get_code(), delivery_site));
    this->agua_cities.insert(std::make_pair(delivery_site.get_city(), delivery_site));
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
    if(pipe.get_direction() == 0)
    {
        addEdge(aguapoints[pipe.get_code_A()],aguapoints[pipe.get_code_B()], pipe);

        pipe.set_inverse_direction();
        addEdge(aguapoints[pipe.get_code_B()],aguapoints[pipe.get_code_A()], pipe);
    }
    else
        addEdge(aguapoints[pipe.get_code_A()],aguapoints[pipe.get_code_B()], pipe);
}
void WMSGraph::add_shadow_pipe(Pipe& pipe)
{
    Pipe shadow_pipe = pipe;

    shadow_pipe.set_capacity(0);

    addEdge(aguapoints[pipe.get_code_B()],aguapoints[pipe.get_code_A()],shadow_pipe);
}

void WMSGraph::remove_pipe(Pipe& pipe)
{
    removeEdge(aguapoints[pipe.get_code_A()], aguapoints[pipe.get_code_B()]);
}

std::unordered_map<std::string, Agua> WMSGraph::get_aguapoints(void) {
    return this->aguapoints;
}

DeliverySite WMSGraph::get_agua_city(std::string city)
{
    std::string new_city = capitalizeFirstLetter(city);

    auto it = agua_cities.find(new_city);

    if (it != agua_cities.end())
    {
        DeliverySite new_delivery_site = it->second;
        return new_delivery_site;
    }
    else
    {
        return DeliverySite(); // later use for checking errors
    }
}