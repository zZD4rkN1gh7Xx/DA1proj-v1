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

#include <iostream>
#include <queue>
#include <unordered_map>
#include <limits>
#include <algorithm>

// Assuming the definitions of WMSGraph, Vertex<Agua>, Pipe, and other related classes

bool bfs(WMSGraph& residual, Vertex<Agua>& source, Vertex<Agua>& sink, std::unordered_map<std::string, Vertex<Agua>*>& parent) {
    for (auto& v : residual.getVertexSet()) {
        v->setVisited(false);
    }
    std::queue<Vertex<Agua>*> q;
    q.push(&source);
    source.setVisited(true);

    while (!q.empty()) {
        Vertex<Agua>* u = q.front();
        q.pop();

        for (auto& edge : u->getAdj()) {
            auto hello = residual.findEdge(u->getInfo(), edge.getDest()->getInfo())->getWeight().get_capacity();
            if (!edge.getDest()->isVisited() && residual.findEdge(u->getInfo(), edge.getDest()->getInfo())->getWeight().get_capacity() > 0) {
                q.push(edge.getDest());
                parent[edge.getDest()->getInfo().get_code()] = u;
                edge.getDest()->setVisited(true);
            }
        }
    }

    return sink.isVisited();
}

int edmondsKarp(WMSGraph& graph, Vertex<Agua>& source, Vertex<Agua>* sink) {
    WMSGraph residual = graph;
    std::unordered_map<std::string, Vertex<Agua>*> parent;
    unordered_map<int, int> results;

    for (auto a : graph.get_agua_city()) {
        if (a.first[1] == 'S') {
            continue;
        }
        else {
            results[a.second.get_id()] = 0;
        }
    }

    int maxFlow = 0;


    Vertex<Agua>* prev_vertex;

    while (bfs(residual, source, *sink, parent)) {
        int pathFlow = std::numeric_limits<int>::max();

        // Find path flow
        Vertex<Agua>* vertex = sink;
        auto prev_vertex = vertex;
        while (vertex->getInfo().get_code() != source.getInfo().get_code()) {
            Vertex<Agua>* next = parent[vertex->getInfo().get_code()];
            auto hello = residual.findEdge(next->getInfo(), vertex->getInfo());
            pathFlow = std::min(pathFlow, hello->getWeight().get_capacity());
            vertex = next;
        }

        // Update residual graph capacities
        vertex = sink;
        while (vertex->getInfo().get_code() != source.getInfo().get_code()) {
            Vertex<Agua>* next = parent[vertex->getInfo().get_code()];
            cout << vertex->getInfo().get_code() << " - ";
            if (vertex->getInfo().get_code()[0] == 'C' && vertex->getInfo().get_code()[1] != 'S') {
                prev_vertex = vertex;
            }
            auto pipe = residual.findEdge(next->getInfo(), vertex->getInfo())->getWeight();

            if (residual.findEdge(next->getInfo(), vertex->getInfo()) != nullptr) {
                auto res_pipe = residual.findEdge(next->getInfo(), vertex->getInfo())->getWeight();
                res_pipe.set_capacity(res_pipe.get_capacity() - pathFlow);
                residual.remove_pipe(residual.findEdge(next->getInfo(), vertex->getInfo())->getWeight());
                residual.add_pipe(res_pipe);
            } else {
                Pipe new_pipe = Pipe(vertex->getInfo().get_code(), next->getInfo().get_code(), pathFlow, 1, residual.get_pipes().size() + 1);
                residual.add_pipe(new_pipe);
            }
            vertex = next;
        }
        cout << pathFlow << endl << endl;

        maxFlow += pathFlow;
        results[prev_vertex->getInfo().get_id()] += pathFlow;
    }

    for (auto a : graph.get_agua_city()) {
        if (a.first[1] == 'S') {
            continue;
        }
        else {
            cout << a.second.get_city() << " - " <<results[a.second.get_id()] <<endl;
        }
    }

    return maxFlow;
}








std::unordered_map<int, int> carry_initializator(WMSGraph global_graph)
{
    std::unordered_map<int, int> carry;

    for(auto pipe : global_graph.get_pipes())
    {
        carry[pipe.first] = 0;
    }

    return carry;
}



vector<std::string> get_city_path(WMSGraph global_graph, Vertex<Agua>* reservoir, Vertex<Agua> * city, std::unordered_map<int, int>& carry, std::unordered_map<int , int>& hard)
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
                if (hard[neighbour.getWeight().get_id()] == 1)
                {
                    hard[neighbour.getWeight().get_id()] = 0;
                    cout << "Go another way! Pipe " << neighbour.getWeight().get_id() << " is going to dry you!" << endl;
                }
                else {
                    neighbour.getDest()->setVisited(true);
                    parents[neighbour.getDest()->getInfo().get_code()] = current->getInfo().get_code();
                    q.push(neighbour.getDest());
                }
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





    if( global_graph.get_city_by_code(path[path.size() -2 ]).get_demand() < receiving + min_pipe )
    {
        min_pipe = global_graph.get_city_by_code(path[path.size() -2 ]).get_demand() - receiving;
    }

    auto capacidade = global_graph.findEdge(global_graph.get_agua_point(path[0]), global_graph.get_agua_point(path[1]))->getWeight().get_capacity();
    auto a_dar = carry[global_graph.findEdge(global_graph.get_agua_point(path[0]), global_graph.get_agua_point(path[1]))->getWeight().get_id()];

    if(capacidade - a_dar == min_pipe) {
        hard[global_graph.findEdge(global_graph.get_agua_point(path[path.size() - 2]), global_graph.get_agua_point(path[path.size() - 1]))->getWeight().get_id()] = 1;
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

    for(auto edge : global_graph.get_pipes()) {
        hard[edge.first] = 0;
    }

    Vertex<Agua>* start_vertex = global_graph.findVertex(source);
    Vertex<Agua>* end_vertex = global_graph.findVertex(sink);


    if (sink.get_id() == 0 || source.get_id() == 0) {
        std::cout << "Didnt find source or sink in Edmonds-Karp func" << std::endl;
        return 0; // Return 0 if source or sink is not found
    }

    path = get_city_path(global_graph,start_vertex,end_vertex, carry, hard); // criar um path inicial

    while (!path.empty() )
    {

        max_flow += returning_water(dummy_graph, shadow_graph ,path,carry, hard);
        path = get_city_path(global_graph,start_vertex,end_vertex,carry, hard); // criar um path diferente
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
