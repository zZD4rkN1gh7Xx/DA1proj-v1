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

unordered_map<int, int> edmondsKarp(WMSGraph& graph, Vertex<Agua>& source, Vertex<Agua>* sink) {
    WMSGraph dummy = graph;
    WMSGraph residual = graph;
    std::unordered_map<std::string, Vertex<Agua>*> parent;
    unordered_map<int, int> results;

    for (auto a : dummy.get_agua_city()) {
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

        maxFlow += pathFlow;
        results[prev_vertex->getInfo().get_id()] += pathFlow;
    }

    return results;
}

int max_flow(WMSGraph global_graph, unordered_map<int, int> results )
{
    int flow = 0;

    for(auto city : results)
    {
        flow += city.second;
    }

    return flow;
}

void show_results(WMSGraph global_graph, unordered_map<int, int> results)
{
    for(int i = 1; i < results.size(); i++)
    {
        if(results[i] == global_graph.get_city_id(i).get_demand())
        {
            std::cout << "The city of " << global_graph.get_city_id(i).get_city() << "(" << global_graph.get_city_id(i).get_code() << ") receives all the needed water of: " << results[i] << "m^3/s." << std::endl;
        }

        else
        {
            std::cout << "The city of " << global_graph.get_city_id(i).get_city() << "(" << global_graph.get_city_id(i).get_code() << ") is it is missing " << global_graph.get_city_id(i).get_demand() - results[i] << "m^3/s." << std::endl;
        }
    }
}



//Perguntas 3

void reservoirs_affected_cities(WMSGraph global_graph,std::string code)
{
    WMSGraph dummy_graph;
    WaterReservoir res = global_graph.get_water_reservoir_code(code);


    dummy_graph = global_graph;

    dummy_graph.remove_water_reservoir(res);


    auto source = dummy_graph.get_super_source();
    auto sink = dummy_graph.get_super_sink();

    auto solve = edmondsKarp(dummy_graph, *source, sink);

    std::cout << "After the removal of the reservor: " << res.get_reservoir() << " the network has a total flow of: " << max_flow(dummy_graph, solve) << std::endl;
    show_results(dummy_graph, solve);

}

void pumping_stations_affected_cities(WMSGraph global_graph)
{
    WMSGraph dummy_graph = global_graph;

    auto source = dummy_graph.get_super_source();
    auto sink = dummy_graph.get_super_sink();

    auto solve = edmondsKarp(dummy_graph, *source, sink);


    for(auto pumping_station : global_graph.get_pumping_stations())
    {
        dummy_graph = global_graph;

        auto pump = pumping_station.second;

        dummy_graph.remove_pumping_station(pump);

        auto without_pumping = edmondsKarp(dummy_graph, *source, sink);

        if( without_pumping == solve)
        {
            std::cout << "After removing the Pumping Station: " << pump.get_code() << ", there were no affected cities" << std::endl;
        }

        else
        {
            std::cout << "After removing the Pumping Station: " << pump.get_code() << ", some cities lost some flow, each were:" << std::endl;
            auto it1 = without_pumping.begin();
            auto it2 = solve.begin();

            while(it1 != without_pumping.end() && it2 != solve.end())
            {

                if(it1->second == it2->second)
                {
                    std::cout << "The city of: " << dummy_graph.get_city_id(it1->first).get_city() << "(" << dummy_graph.get_city_id(it1->first).get_code() << ") did not suffer any loss in flow. (current flow: " << it1->second << ")." << std::endl;
                }
                else
                {
                    std::cout << "The city of: " << dummy_graph.get_city_id(it1->first).get_city() << "(" << dummy_graph.get_city_id(it1->first).get_code() << ") suffered a loss in flow of: " <<  it2->second - it1->second   << " (current flow: " << it1->second << ")." << std::endl;
                }

                ++it1;
                ++it2;
            }
        }

    }
}



#endif //DAPROJ_V1_SOLUÇAO_H
