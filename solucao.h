//
// Created by Administrador on 04/04/2024.
//

/**

    *@file solucao.h
    *@brief Functions needed to solve the project
*/

#ifndef DAPROJ_V1_SOLUÇAO_H
#define DAPROJ_V1_SOLUÇAO_H

#include "WMSGraph.h"
#include "helpfunctions.h"
#include "FileReader.h"
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

void file_add(WMSGraph &grafo, int regiao) {
    /**

    *@return adds the info to the graph according the region chosen*
    *@param grafo,regiao  graph that we will bea adding its properties and the region will be working on*
    Complexity O(n + m + p)*/
    if (regiao == 0) {
        FileReader::add_cities("../Project1DataSetSmall/Project1DataSetSmall/Cities_Madeira.csv", grafo);

        FileReader::add_reservoirs("../Project1DataSetSmall/Project1DataSetSmall/Reservoirs_Madeira.csv", grafo);

        FileReader::add_stations("../Project1DataSetSmall/Project1DataSetSmall/Stations_Madeira.csv", grafo);

        FileReader::add_pipes("../Project1DataSetSmall/Project1DataSetSmall/Pipes_Madeira.csv", grafo);
    }

    if (regiao == 1) {
        FileReader::add_cities("../Project1LargeDataSet/Project1LargeDataSet/Cities.csv", grafo);

        FileReader::add_reservoirs("../Project1LargeDataSet/Project1LargeDataSet/Reservoir.csv", grafo);

        FileReader::add_stations("../Project1LargeDataSet/Project1LargeDataSet/Stations.csv", grafo);

        FileReader::add_pipes("../Project1LargeDataSet/Project1LargeDataSet/Pipes.csv", grafo);
    }

    int count = 0;

    WaterReservoir super_res = WaterReservoir("super", "RS_2", grafo.get_agua_reservoir().size() + 1, "RS_2", 0);
    DeliverySite super_del = DeliverySite("City Super", grafo.get_agua_city().size() + 1, "CS_2", 0, 0);

    for (auto reservoir: grafo.get_agua_reservoir()) // inicaliazdor das cidades que cada reservatoio chega
    {
        super_res.set_max_delivery(super_res.get_max_delivery() + reservoir.second.get_max_delivery());
    }

    grafo.add_water_reservoir(super_res);

    for (auto reservoir: grafo.get_agua_reservoir()) // inicaliazdor das cidades que cada reservatoio chega
    {
        if (reservoir.second != super_res) {
            count++;
            Pipe pipe;
            pipe = Pipe("RS_2", reservoir.second.get_code(), reservoir.second.get_max_delivery(), 1,grafo.get_pipes().size() + count + 24 + reservoir.second.get_max_delivery() + reservoir.second.get_id());

            grafo.add_pipe(pipe);
        }
    }

    count = 0;

    for (auto sink: grafo.get_agua_city()) {
        super_del.set_demand(super_del.get_demand() + sink.second.get_demand());
    }

    grafo.add_delivery_site(super_del);


    for (auto sink: grafo.get_agua_city()) // inicaliazdor das cidades que cada reservatorio chega
    {
        if (sink.second != super_del) {
            count++;
            auto pipe = Pipe(sink.second.get_code(), "CS_2", sink.second.get_demand(), 1,grafo.get_pipes().size() + count);

            grafo.add_pipe(pipe);
        }
    }
}



bool without_bfs(WMSGraph& residual, Vertex<Agua> remove, Vertex<Agua>& source, Vertex<Agua>& sink, std::unordered_map<std::string, Vertex<Agua>*>& parent) {
    /**

*@return returns true if theres a path between sorce and sink according the flow each pipe has and does not crosses a certain chosen vertex*
*@param residual, remove, source, sink, parent  the residual values for edmonds karp the vertex to igore the source and the sink and each vertex "parents"*
Complexity O(n + m + p)*/
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
            if (!edge.getDest()->isVisited() && residual.get_pipe_id(residual.findEdge(u->getInfo(), edge.getDest()->getInfo())->getWeight().get_id()).get_capacity() > 0 && edge.getDest()->getInfo().get_code() != remove.getInfo().get_code()) {
                q.push(edge.getDest());
                parent[edge.getDest()->getInfo().get_code()] = u;
                edge.getDest()->setVisited(true);
            }
        }
    }

    return sink.isVisited();
}

bool bfs(WMSGraph& residual, Vertex<Agua>& source, Vertex<Agua>& sink, std::unordered_map<std::string, Vertex<Agua>*>& parent) {
    /**

*@return returns true if theres a path between sorce and sink according the flow each pipe has.*
*@param residual, source, sink, parent  the residual values for edmonds karp the vertex to igore the source and the sink and each vertex "parents"*
Complexity O(n + m + p)*/
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
            if (!edge.getDest()->isVisited() && residual.get_pipe_id(residual.findEdge(u->getInfo(), edge.getDest()->getInfo())->getWeight().get_id()).get_capacity() > 0) {
                q.push(edge.getDest());
                parent[edge.getDest()->getInfo().get_code()] = u;
                edge.getDest()->setVisited(true);
            }
        }
    }

    return sink.isVisited();
}

unordered_map<int, int> without_edmondsKarp(WMSGraph graph, Vertex<Agua>& without, Vertex<Agua>& source, Vertex<Agua>* sink) {
    /**

*@return returns the flow on each city acording their ID*
*@param graph, without, source, sink  the  graph to cross the vertex to ignore and the sink and sorce of the graph*
Complexity O((V + E) * V + V + M)
     */
    WMSGraph dummy = graph;
    WMSGraph residual = graph;
    std::unordered_map<std::string, Vertex<Agua>*> parent;
    unordered_map<int, int> results;
    auto v = graph.getVertexSet();

    for (auto a : dummy.get_agua_city()) {
        if (a.first[1] == 'S') {
            continue;
        }
        else {
            results[a.second.get_id()] = 0;
        }
    }


    int maxFlow = 0;


    while (without_bfs(residual, without, source, *sink, parent)) {
        int pathFlow = std::numeric_limits<int>::max();
        // Find path flow
        Vertex<Agua>* vertex = sink;
        auto prev_vertex = vertex;
        while (vertex->getInfo().get_code() != source.getInfo().get_code()) {
            Vertex<Agua>* next = parent[vertex->getInfo().get_code()];
            auto deixaver = residual.get_pipe_id(residual.findEdge(next->getInfo(), vertex->getInfo())->getWeight().get_id());
            auto hello = residual.get_pipe_id(residual.findEdge(next->getInfo(), vertex->getInfo())->getWeight().get_id()).get_capacity();
            pathFlow = std::min(pathFlow, hello);
            vertex = next;
        }

        // Update residual graph capacities
        vertex = sink;
        while (vertex->getInfo().get_code() != source.getInfo().get_code()) {
            Vertex<Agua>* next = parent[vertex->getInfo().get_code()];
            if (vertex->getInfo().get_code()[0] == 'C' && vertex->getInfo().get_code()[1] != 'S') {
                prev_vertex = vertex;
            }
            auto pipe = residual.get_pipe_id(residual.findEdge(next->getInfo(), vertex->getInfo())->getWeight().get_id());

            if (residual.findEdge(next->getInfo(), vertex->getInfo()) != nullptr) {
                auto res_pipe = residual.get_pipe_id(residual.findEdge(next->getInfo(), vertex->getInfo())->getWeight().get_id());
                res_pipe.set_capacity(res_pipe.get_capacity() - pathFlow);
                residual.remove_pipe(residual.get_pipe_id(residual.findEdge(next->getInfo(), vertex->getInfo())->getWeight().get_id()));
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

    graph.setVertexSet(v);
    residual.setVertexSet(v);
    return results;
}


unordered_map<int, int> edmondsKarp(WMSGraph graph, Vertex<Agua>& source, Vertex<Agua>* sink) {
    /**

*@return returns the flow on each city acording their ID*
*@param graph, without, source, sink  the  graph to cross the vertex to ignore and the sink and sorce of the graph*
Complexity O((V + E) * V + V + M)*/
    WMSGraph dummy = graph;
    WMSGraph residual = graph;
    auto v = graph.getVertexSet();
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

    while (bfs(residual,source, *sink, parent)) {
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

    graph.setVertexSet(v);
    residual.setVertexSet(v);
    return results;
}

int max_flow(WMSGraph global_graph, unordered_map<int, int> results )
{
    /**

*@return returns the flow on each city acording their ID*
*@param graph, without, source, sink  the  graph to cross the vertex to ignore and the sink and sorce of the graph*
Complexity O((V + E) * V + V + M)*/
    int flow = 0;

    for(auto city : results)
    {
        flow += city.second;
    }

    return flow;
}

void show_results(WMSGraph global_graph, unordered_map<int, int> results, unordered_map<int, int> prev)
{
    /**

@return returns the flow on each city acording their ID*
@param graph, without, source, sink  the  graph to cross the vertex to ignore and the sink and sorce of the graph*
Complexity O((V + E) * V + V + M)*/

    for(int i = 1; i < results.size(); i++)
    {
        if(results[i] == prev[i])
        {
            std::cout << "The city of " << global_graph.get_city_id(i).get_city() << "(" << global_graph.get_city_id(i).get_code() << ") receives the same ammount of water as before: " << results[i] << "m^3/s." << std::endl;
        }

        else
        {
            std::cout << "The city of " << global_graph.get_city_id(i).get_city() << "(" << global_graph.get_city_id(i).get_code() << ") is missing " << prev[i] - results[i] << "m^3/s." << std::endl;
        }
    }
}



//Perguntas 3

void reservoirs_affected_cities(int regiao, std::string code)
{
    WMSGraph dummy_graph;

    file_add(dummy_graph, regiao);

    WaterReservoir res = dummy_graph.get_water_reservoir_code(code);


    auto source = dummy_graph.get_super_source();
    auto sink = dummy_graph.get_super_sink();

    auto solve2 = without_edmondsKarp(dummy_graph, *dummy_graph.findVertex(dummy_graph.get_agua_point(code)), *source, sink);

    WMSGraph killmyself2;
    file_add(killmyself2, regiao);

    auto source2 = killmyself2.get_super_source();
    auto sink2 = killmyself2.get_super_sink();

    auto solve = edmondsKarp(killmyself2, *source2, sink2);

    std::cout << "After the removal of the reservor: " << res.get_reservoir() << " the network has a total flow of: " << max_flow(dummy_graph, solve2) << std::endl;
    show_results(dummy_graph, solve2, solve);

}

bool pumping_stations_affected_cities(int regiao, std::unordered_map<int, int> expected, std::string code)
{
    /**

*@return shows us the affected cities after removing a pumping station*
*@param regiao the region we will be working on*
Complexity O((V + E) * V + V + n*/
    bool affecting = false;
    WMSGraph dummy_graph;

    file_add(dummy_graph, regiao);

    auto source = dummy_graph.get_super_source();
    auto sink = dummy_graph.get_super_sink();

    auto solve = without_edmondsKarp(dummy_graph, *dummy_graph.findVertex(dummy_graph.get_agua_point(code)),*source, sink);


        WMSGraph place_holder;

        file_add(place_holder, regiao);

        auto pump = place_holder.get_pumping_station_code(place_holder.get_agua_point(code));


        if(expected != solve)
        {
            affecting = true;
        }

        std::cout << endl << "After removing " << pump.get_code() << ": " << endl;
        auto it1 = expected.begin();
        auto it2 = solve.begin();

        while(it1 != expected.end() && it2 != solve.end()) {

            std::cout << "The city " << place_holder.get_city_id(it1->first).get_code() << " has " << it1->second << " flow (" << abs(it2->second - it1->second) << " deficit)" << std::endl;

            ++it1;
            ++it2;
        }

        return affecting;
}

bool pipes_affected_cities(int regiao, unordered_map<int, int> expected, Pipe pipe)
{

    bool affecting = false;

    WMSGraph solution;

    file_add(solution, regiao);

    auto sol = edmondsKarp(solution, *solution.get_super_source(), solution.get_super_sink());


        WMSGraph dummy;
        file_add(dummy, regiao);

            Pipe new_pipe = pipe;
            dummy.remove_pipe(pipe);
            new_pipe.set_capacity(0);
            dummy.add_pipe(new_pipe);


            auto capacities = edmondsKarp(dummy, *dummy.get_super_source(), dummy.get_super_sink());

            if(capacities != expected) {
                affecting = true;
                cout << "The Pipe ("<< new_pipe.get_code_A() << " - " << new_pipe.get_code_B() << ") affects: " << endl;
                for(int i = 1; i < capacities.size(); i++)
                {
                    auto city = dummy.get_city_id(i);

                    if(capacities[i] < city.get_demand())
                    {
                        std::cout << "The city " << city.get_code() << " (" << expected[city.get_id()] - capacities[i] << ")" << std::endl;
                    }

                }
           }
            else
            {
                std::cout << "The Pipe (" << new_pipe.get_code_A() << " - " << new_pipe.get_code_B() << ") doesn't affect the network flow."<< std::endl << std::endl;
                cout << "The Pipe ("<< new_pipe.get_code_A() << " - " << new_pipe.get_code_B() << ") affects: " << endl;
                for(int i = 1; i < capacities.size(); i++)
                {
                    auto city = dummy.get_city_id(i);

                    if(capacities[i] < city.get_demand())
                    {
                        std::cout << "The city " << city.get_code() << " (" << expected[city.get_id()] - capacities[i] << ")" << std::endl;
                    }

                }
            }
            return affecting;


}



#endif //DAPROJ_V1_SOLUÇAO_H
