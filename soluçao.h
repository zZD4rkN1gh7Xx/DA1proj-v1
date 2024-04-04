//
// Created by Administrador on 04/04/2024.
//

#ifndef DAPROJ_V1_SOLUÇAO_H
#define DAPROJ_V1_SOLUÇAO_H

#include "WMSGraph.h"
#include "helpfunctions.h"
#include <string>
#include <iostream>
#include <queue>
#include <limits>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <set>
#include <algorithm>


std::unordered_map<int, int> carry_initializator(WMSGraph global_graph)
{
    std::unordered_map<int, int> carry;

    for(auto pipe : global_graph.get_pipes())
    {
        carry[pipe.first] = 0;
    }

    return carry;
}



vector<std::string> get_city_path(WMSGraph global_graph, Vertex<Agua>* reservoir, Vertex<Agua> * city, std::unordered_map<int, int>& carry, std::unordered_map<int , int> hard)
{
    global_graph.set_all_unvisited(global_graph.getVertexSet());
    unordered_map<std::string, std::string> parents;
    queue<Vertex<Agua> * > q;
    vector<std::string> path;

    q.push(reservoir);

    while(!q.empty())
    {
        auto current = q.front();
        q.pop();

        if(current->getInfo().get_code() == city->getInfo().get_code())
        {
            auto child = current->getInfo().get_code();
            path.push_back(child);

            while(parents[child] != reservoir->getInfo().get_code()) //se fosse child != como estava ficava um valor "" no vetor path
            {
                path.push_back(parents[child]);
                child = parents[child];
            }

            path.push_back(parents[child]);
            std::reverse(path.begin(), path.end());
            return path;
        }

        for(auto neighbour : current->getAdj())
        {
            if ((neighbour.getWeight().get_capacity() > carry[neighbour.getWeight().get_id()]) && !neighbour.getDest()->isVisited() ) // caso o pipe nao esteja full e nao esteja visited
            {

                // fazia ciclo infinito, ver se continua certo
                neighbour.getDest()->setVisited(true);
                parents[neighbour.getDest()->getInfo().get_code()] = current->getInfo().get_code();
                q.push(neighbour.getDest());
            }
        }
    }

    return path;

}

int returning_water(WMSGraph& global_graph,WMSGraph shadow_graph , vector<std::string> path, std::unordered_map<int, int>& carry, std::unordered_map<int, int>& hard)
{

    int min_pipe = INT_MAX;
    int receiving = 0;

    for(auto it = path.begin(); it != (path.end() - 1); it++)
    {
        auto edge = global_graph.findEdge(global_graph.get_agua_point(*it), global_graph.get_agua_point(*(it + 1)));

        if(min_pipe > (edge->getWeight().get_capacity() - carry[edge->getWeight().get_id()]))
        {
            min_pipe = (edge->getWeight().get_capacity() - carry[edge->getWeight().get_id()]);
        }
    }

    for(auto getting : shadow_graph.findVertex(shadow_graph.get_agua_point(path[path.size() - 2]))->getAdj() )
    {
        receiving += carry[getting.getWeight().get_id()];
    }

    hard[global_graph.findEdge(global_graph.get_agua_point(path[0]), global_graph.get_agua_point(path[1]))->getWeight().get_id()] = 0;

    if( carry[global_graph.findEdge(global_graph.get_agua_point(path[0]), global_graph.get_agua_point(path[1]))->getWeight().get_id()] - min_pipe == 0)
    {
        hard[global_graph.findEdge(global_graph.get_agua_point(path[0]), global_graph.get_agua_point(path[1]))->getWeight().get_id()] = 1;
    }



    if( global_graph.get_city_by_code(path[path.size() -2 ]).get_demand() < receiving + min_pipe )
    {
        min_pipe = global_graph.get_city_by_code(path[path.size() -2 ]).get_demand() - receiving;
    }

    std::cout << min_pipe << std::endl;



    for(auto it = path.begin(); it != (path.end() - 1); it++)
    {
        auto edge = global_graph.findEdge(global_graph.get_agua_point(*it), global_graph.get_agua_point(*(it + 1)));

        carry[edge->getWeight().get_id()] += min_pipe;
    }

    return min_pipe;
}




int edmonds_karp(Agua sink, Agua source, WMSGraph& global_graph, WMSGraph& shadow_graph ,std::unordered_map<int, int>& carry) {

    global_graph.set_all_unvisited(global_graph.getVertexSet()); // Reset visited flags

    int max_flow = 0; // Initialize max flow
    vector<std::string> path;
    std::queue<Vertex<Agua>*> q;
    WMSGraph dummy_graph = global_graph;
    std::unordered_map<int , int> hard;

    Vertex<Agua>* start_vertex = global_graph.findVertex(source);
    Vertex<Agua>* end_vertex = global_graph.findVertex(sink);


    if (sink.get_id() == 0 || source.get_id() == 0) {
        std::cout << "Didnt find source or sink in Edmonds-Karp func" << std::endl;
        return 0; // Return 0 if source or sink is not found
    }

    path = get_city_path(global_graph,start_vertex,end_vertex, carry, hard); // criar um path inicial

    while (!path.empty() )
    {

        max_flow += returning_water(dummy_graph, shadow_graph ,path,carry);
        path = get_city_path(global_graph,start_vertex,end_vertex,carry); // criar um path diferente
    }

    return max_flow;
}

int is_it_enough(WMSGraph& global_graph, WMSGraph& shadow_graph) {
    std::unordered_map<int, int> carry; // What each pipe will be able to give ( max at pipe capacity)
    Pipe pipe;
    int count = 0;

    WaterReservoir super_res = WaterReservoir("super", "RS_2", global_graph.get_agua_reservoir().size() + 1, "RS_2", 0);
    DeliverySite super_del = DeliverySite("City Super", global_graph.get_agua_city().size() + 1, "CS_2", 0, 0);

    for (auto reservoir: global_graph.get_agua_reservoir()) // inicaliazdor das cidades que cada reservatoio chega
    {
        super_res.set_max_delivery(super_res.get_max_delivery() + reservoir.second.get_max_delivery());
    }

    global_graph.add_water_reservoir(super_res);
    shadow_graph.add_water_reservoir(super_res);

    for (auto reservoir: global_graph.get_agua_reservoir()) // inicaliazdor das cidades que cada reservatoio chega
    {
        if (reservoir.second != super_res) {
            count++;
            Pipe pipe;
            pipe = Pipe("RS_2", reservoir.second.get_code(), reservoir.second.get_max_delivery(), 1,global_graph.get_pipes().size() + count);

            global_graph.add_pipe(pipe);
            shadow_graph.add_shadow_pipe(pipe);
        }
    }

    count = 0;

    for (auto sink: global_graph.get_agua_city()) {
        super_del.set_demand(super_del.get_demand() + sink.second.get_demand());
    }

    global_graph.add_delivery_site(super_del);
    shadow_graph.add_delivery_site(super_del);

    for (auto sink: global_graph.get_agua_city()) // inicaliazdor das cidades que cada reservatoio chega
    {
        if (sink.second != super_del) {
            count++;
            pipe = Pipe(sink.second.get_code(), "CS_2", sink.second.get_demand(), 1,global_graph.get_pipes().size() + count);

            global_graph.add_pipe(pipe);
            shadow_graph.add_shadow_pipe(pipe);
        }
    }

    carry = carry_initializator(global_graph);
    int kk = edmonds_karp(super_del, super_res, global_graph, shadow_graph, carry);

    for (auto a: global_graph.get_agua_city()) {
        if (a.second.get_code() != "CS_2")
            cout << a.second.get_city() << " "
                 << carry[global_graph.findVertex(a.second)->getAdj()[0].getWeight().get_id()] << std::endl ;
    }


    std::cout << endl << endl;
    for(auto a : global_graph.findVertex(super_res)->getAdj())
    {
        std::cout  << global_graph.get_water_reservoir_code(a.getDest()->getInfo()).get_reservoir() << " " << carry[a.getWeight().get_id()] << endl;
    }

    return kk;
}


//Perguntas 3

void reservoirs_affected_cities(WMSGraph global_graph, WMSGraph shadow_graph, WaterReservoir reservoir)
{
    WMSGraph dummy_graph;
    WMSGraph shadow_dummy_graph;

    dummy_graph = global_graph;
    shadow_dummy_graph = shadow_graph;

    dummy_graph.remove_water_reservoir(reservoir);
    shadow_dummy_graph.remove_water_reservoir(reservoir);

    is_it_enough(dummy_graph, shadow_dummy_graph);
}

void pumping_stations_affected_cities(WMSGraph global_graph, WMSGraph shadow_graph)
{
    WMSGraph dummy_graph;
    WMSGraph shadow_dummy_graph;

    dummy_graph = global_graph;
    shadow_dummy_graph = shadow_graph;


    for(auto pumping_station : global_graph.get_pumping_stations())
    {
        auto pump = pumping_station.second;

    }
}



#endif //DAPROJ_V1_SOLUÇAO_H
