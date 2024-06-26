//
// Created by Administrador on 20/03/2024.
//

/**
    *@file WMSGraph.cpp
    *@brief Implementation of the WMSGraph class methods
*/

#include "WMSGraph.h"


void WMSGraph::add_delivery_site(DeliverySite& delivery_site)
{
    addVertex(delivery_site);
    this->aguapoints.insert(std::make_pair(delivery_site.get_code(), delivery_site));
    this->agua_cities_name.insert(std::make_pair(delivery_site.get_city(), delivery_site));
    this->agua_cities_code.insert(std::make_pair(delivery_site.get_code(), delivery_site));
}


void WMSGraph::add_pumping_station(PumpingStation& pumping_station)
{
    addVertex(pumping_station);
    this->aguapoints.insert(std::make_pair(pumping_station.get_code(), pumping_station));
    this->agua_pumping_stations_code.insert(std::make_pair(pumping_station.get_code(), pumping_station));
    this->agua_pumping_stations.insert(std::make_pair(pumping_station.get_id(), pumping_station));
}

void WMSGraph::add_water_reservoir(WaterReservoir& water_reservoir)
{
    addVertex(water_reservoir);
    this->aguapoints.insert(std::make_pair(water_reservoir.get_code(), water_reservoir));
    this->agua_water_reservoir_code.insert(std::make_pair(water_reservoir.get_code(), water_reservoir));
    this->agua_water_reservoir_name.insert(std::make_pair(capitalizeFirstLetter(water_reservoir.get_reservoir()), water_reservoir));

}



void WMSGraph::add_pipe(Pipe& pipe)
{
    if (pipe.get_code_B()[0] == 'C') {
        pipe.set_city_link(true);
    }
    if(pipe.get_direction() == 0)
    {
        addEdge(aguapoints[pipe.get_code_A()],aguapoints[pipe.get_code_B()], pipe);
        this->agua_pipes.insert(std::make_pair(pipe.get_id(), pipe));
        pipe.set_inverse_direction();
        addEdge(aguapoints[pipe.get_code_B()],aguapoints[pipe.get_code_A()], pipe);

    }
    else {
        addEdge(aguapoints[pipe.get_code_A()], aguapoints[pipe.get_code_B()], pipe);
        this->agua_pipes.insert(std::make_pair(pipe.get_id(), pipe));
    }
}


void WMSGraph::remove_pipe(Pipe pipe)
{
    if (pipe.get_direction() == 0) {
        removeEdge(aguapoints[pipe.get_code_A()], aguapoints[pipe.get_code_B()]);
        removeEdge(aguapoints[pipe.get_code_B()], aguapoints[pipe.get_code_A()]);
        agua_pipes.erase(pipe.get_id());
    }
    else removeEdge(aguapoints[pipe.get_code_A()], aguapoints[pipe.get_code_B()]);
    agua_pipes.erase(pipe.get_id());
}


Agua WMSGraph::get_agua_point(std::string agua_point)
{
    return aguapoints[agua_point];
}




std::unordered_map<std::string, WaterReservoir> WMSGraph::get_agua_reservoir()
{
    return this->agua_water_reservoir_code;
}

std::unordered_map<std::string, DeliverySite> WMSGraph::get_agua_city()
{
    return this->agua_cities_code;
}



DeliverySite WMSGraph::get_city_by_code(std::string code)
{
    auto it = agua_cities_code.find(code);

    if(it != agua_cities_code.end())
    {
        DeliverySite new_delivery_site = it->second;
        return new_delivery_site;
    }
    else
    {
        return DeliverySite(); // later use to check errors
    }
}

PumpingStation WMSGraph::get_pumping_station_code(Agua agua)
{
    auto it = agua_pumping_stations_code.find(agua.get_code());

    if(it != agua_pumping_stations_code.end())
    {
        PumpingStation new_pumping_station = it->second;
        return new_pumping_station;
    }
    else
    {
        return PumpingStation(); // later use to check errors
    }
}




Pipe WMSGraph::get_pipe_id(int id)
{
    auto it = agua_pipes.find(id);

    if(it != nullptr)
    {
        Pipe new_pipe = it->second;
        return new_pipe;
    }
    else
    {
        return Pipe(); // later use to check errors
    }
}


WaterReservoir WMSGraph::get_water_reservoir_code(std::string code)
{
    auto it = agua_water_reservoir_code.find(code);

    if(it != agua_water_reservoir_code.end())
    {
        WaterReservoir new_water_reservoir = it->second;
        return new_water_reservoir;
    }
    else
    {
        return WaterReservoir(); // later use to check errors
    }
}


std::unordered_map<int, Pipe> WMSGraph::get_pipes(void)
{
    return this->agua_pipes;
}



std::unordered_map<std::string, PumpingStation> WMSGraph::get_pumping_stations()
{
    return this->agua_pumping_stations_code;
}

DeliverySite WMSGraph::get_city_id(int id)
{
    for(auto a : get_agua_city())
    {
        if(a.second.get_id() == id)
            return a.second;
    }

    return DeliverySite();
}

Vertex<Agua> * WMSGraph::get_super_sink()
{
    return findVertex(get_agua_point("CS_2"));
}

Vertex<Agua> * WMSGraph::get_super_source()
{
    return findVertex(get_agua_point("RS_2"));
}

WMSGraph::WMSGraph(WMSGraph &graph) {
    this->aguapoints = graph.aguapoints;
    this->agua_pipes = graph.agua_pipes;
    this->agua_cities_code = graph.agua_cities_code;
    this->agua_pumping_stations = graph.agua_pumping_stations;
    this->agua_pumping_stations_code = graph.agua_pumping_stations_code;
    this->agua_water_reservoir_code = graph.agua_water_reservoir_code;
    this->agua_cities_name = graph.agua_cities_name;
    this->agua_water_reservoir_name = graph.agua_water_reservoir_name;
    this->setVertexSet(graph.getVertexSet());
}

WMSGraph::WMSGraph() {

}
