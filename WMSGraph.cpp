//
// Created by Administrador on 20/03/2024.
//

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

    auto it2 = agua_pumping_stations.find(pumping_station.get_id());

    if (it2 != agua_pumping_stations.end()) {
        agua_pumping_stations.erase(it2);
    }
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
void WMSGraph::add_shadow_pipe(Pipe& pipe)
{
    Pipe shadow_pipe = pipe;

    shadow_pipe.set_capacity(0);

    addEdge(aguapoints[pipe.get_code_B()],aguapoints[pipe.get_code_A()],shadow_pipe);
    this->agua_pipes.insert(std::make_pair(pipe.get_id(), pipe));

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

std::unordered_map<std::string, Agua> WMSGraph::get_aguapoints(void) {
    return this->aguapoints;
}

Agua WMSGraph::get_agua_point(std::string agua_point)
{
    return aguapoints[agua_point];
}

DeliverySite WMSGraph::get_agua_city_name(std::string city)
{
    std::string new_city = capitalizeFirstLetter(city);

    auto it = agua_cities_name.find(new_city);

    if (it != agua_cities_name.end())
    {
        DeliverySite new_delivery_site = it->second;
        return new_delivery_site;
    }
    else
    {
        return DeliverySite(); // later use for checking errors
    }
}

WaterReservoir WMSGraph::get_agua_reservoir_name(std::string reservoir)
{
    std::string new_city = capitalizeFirstLetter(reservoir);

    auto it = agua_water_reservoir_name.find(new_city);

    if (it != agua_water_reservoir_name.end())
    {
        WaterReservoir new_delivery_site = it->second;
        return new_delivery_site;
    }
    else
    {
        return WaterReservoir(); // later use for checking errors
    }
}

std::unordered_map<std::string, WaterReservoir> WMSGraph::get_agua_reservoir()
{
    return this->agua_water_reservoir_code;
}

std::unordered_map<std::string, DeliverySite> WMSGraph::get_agua_city()
{
    return this->agua_cities_code;
}

DeliverySite WMSGraph::get_agua_city_code(Agua agua)
{
    auto it = agua_cities_code.find(agua.get_code());

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

PumpingStation WMSGraph::get_pumping_station(int id) {
    auto it = agua_pumping_stations.find(id);

    if(it != nullptr)
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

void WMSGraph::set_all_unvisited(const vector<Vertex<Agua> * >& all_agua)
{
    for(Vertex<Agua>* agua : all_agua)
    {
        agua->setVisited(false);
    }
}

void WMSGraph::reset_shadow_capacities(void)
{
    for(auto& agua_point : getVertexSet())
    {
        for(auto& pipes : agua_point->getAdj())
        {
            Pipe new_pipe = pipes.getWeight();
            new_pipe.set_capacity(0);
            pipes.setWeight(new_pipe);
        }
    }
}


std::vector<Agua> WMSGraph::get_all_sources(std::string sink)
{

    DeliverySite actual_sink = get_agua_city_name(sink);

    // Marcar todos os vértices como não visitados
    for (auto vertex : getVertexSet()) {
        vertex->setVisited(false);
    }

    std::vector<Agua> sources;
    std::queue<Vertex<Agua>*> q;

    Vertex<Agua>* sinkVertex = findVertex(actual_sink);
    if (sinkVertex == nullptr) {
        std::cerr << "Erro: Cidade de destino não encontrada no grafo." << std::endl;
        return sources; // Retorna vetor vazio se o destino não for encontrado
    }

    q.push(sinkVertex);
    sinkVertex->setVisited(true);

    while (!q.empty()) {
        Vertex<Agua>* currentVertex = q.front();
        q.pop();

        bool isSource = true;

        for (const Edge<Agua>& edge : currentVertex->getAdj()) {
            Vertex<Agua>* adjacentVertex = edge.getDest();

            if (!adjacentVertex->isVisited()) {
                q.push(adjacentVertex);
                adjacentVertex->setVisited(true);
                isSource = false;
            }
        }

        if (isSource) {
            if (currentVertex->getInfo().get_code()[0] == 'R')
                sources.push_back(currentVertex->getInfo());
        }
    }

    return sources;
}

std::unordered_map<int, Pipe> WMSGraph::get_pipes(void)
{
    return this->agua_pipes;
}


int WMSGraph::get_total_num_of_edges(void)
{
    int total_edges = 0;
    for(auto vertex : getVertexSet())
    {
        total_edges += vertex->getAdj().size();
    }

    return total_edges;
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
