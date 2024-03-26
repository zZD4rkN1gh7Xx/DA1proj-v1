//
// Created by Administrador on 26/03/2024.
//

#ifndef DAPROJ_V1_TAREFAS_H
#define DAPROJ_V1_TAREFAS_H

#include "WMSGraph.h"
#include "helpfunctions.h"
#include <string>
#include <iostream>
#include <queue>


int edmonds_karp(std::string city, WMSGraph global_graph, WMSGraph shadow_graph)
{

    Agua sink = global_graph.get_agua_city_name(capitalizeFirstLetter(city)); // nosso sink

    vector<Agua> sources = global_graph.get_all_sources(capitalizeFirstLetter(city)); // nossas sorces

    vector<Vertex<Agua>> water_path;

    for(auto& sorce : sources) // fazer o edmonds-karp por todas as sorces para termos a certa max
    {
        global_graph.set_all_unvisited(global_graph.getVertexSet()); // por mos todos os nodes em unvisited para todas as iteraçoes do edmonds karp

        Vertex<Agua> * start_vertex = global_graph.findVertex(sorce); // ir buscar o vertex para o bfs
        std::queue<Vertex<Agua> *> q; // queue de nodes a visitar

        q.push(start_vertex);
        start_vertex->setVisited(true);

        while(!q.empty())
        {
            auto& current = q.front();
            q.pop();

            for(auto& edge : current->getAdj())
            {
                Vertex<Agua> *destination = edge.getDest();

                if(!destination->isVisited() && edge.getWeight().get_capacity() > 0)
                {
                    q.push(edge.getDest());
                    edge.getDest()->setVisited(true);

                }
            }


        }


    }



}





#endif //DAPROJ_V1_TAREFAS_H
