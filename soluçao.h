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


vector<std::string> get_city_path(WMSGraph global_graph, Vertex<Agua>* reservoir, Vertex<Agua> * city)
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
            if ((neighbour.getWeight().get_capacity() > 0) && !neighbour.getDest()->isVisited()) // caso o pipe nao esteja full e nao esteja visited
            {// fazia ciclo infinito, ver se continua certo
                neighbour.getDest()->setVisited(true);
                parents[neighbour.getDest()->getInfo().get_code()] = current->getInfo().get_code();
                q.push(neighbour.getDest());
            }
        }
    }

    return path;
}

int returning_water(WMSGraph& global_graph, vector<std::string> path)
{
    int min_pipe = INT_MAX;

    for(auto it = path.begin(); it != (path.end() - 1); it++)
    {
        auto edge = global_graph.findEdge(global_graph.get_agua_point(*it), global_graph.get_agua_point(*(it + 1)));

        if(min_pipe > edge->getWeight().get_capacity())
            min_pipe = edge->getWeight().get_capacity();
    }

    for(auto it = path.begin(); it != (path.end() - 1); it++)
    {
        auto edge = global_graph.findEdge(global_graph.get_agua_point(*it), global_graph.get_agua_point(*(it + 1)));

        edge->getWeight().set_capacity(edge->getWeight().get_capacity() - min_pipe);
    }

    return min_pipe;
}




int edmonds_karp(Agua sink, Agua source, WMSGraph& global_graph) {

    global_graph.set_all_unvisited(global_graph.getVertexSet()); // Reset visited flags

    int max_flow = 0; // Initialize max flow
    vector<std::string> path;
    std::queue<Vertex<Agua>*> q;
    WMSGraph dummy_graph = global_graph;

    Vertex<Agua>* start_vertex = global_graph.findVertex(source);
    Vertex<Agua>* end_vertex = global_graph.findVertex(sink);


    if (sink.get_id() == 0 || source.get_id() == 0) {
        std::cout << "Didnt find source or sink in Edmonds-Karp func" << std::endl;
        return 0; // Return 0 if source or sink is not found
    }

    path = get_city_path(global_graph,start_vertex,end_vertex); // criar um path inicial

    while (!path.empty() )
    {
        max_flow += returning_water(dummy_graph,path);
        path = get_city_path(global_graph,start_vertex,end_vertex); // criar um path diferente
    }

    return max_flow;
}




#endif //DAPROJ_V1_SOLUÇAO_H
