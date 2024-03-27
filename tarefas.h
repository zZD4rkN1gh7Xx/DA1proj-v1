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
#include <limits>
#include <unordered_map>


// nao esquecer de que o input do glogal graph tem de ser uma copia para nao alterarmos o grafo oriiginal
int edmonds_karp(std::string city, std::string reservoir, WMSGraph& global_graph) {

    global_graph.set_all_unvisited(global_graph.getVertexSet()); // volta a dar set up aos vertexes caso outras funçoes nao tenham deixado


    Agua sink = global_graph.get_agua_city_name(capitalizeFirstLetter(city)); // Destination
    Agua source = global_graph.get_agua_reservoir_name(capitalizeFirstLetter(reservoir)); // Source
    std::cout << source.get_code() << endl << endl;
    if(sink.get_id() == 0 || source.get_id() == 0)
        std::cout << "Didnt find source or sink in edmonds karp func";

    else
    {
        int max_flow = 0; // Initialize max flow

        Vertex<Agua> *start_vertex = global_graph.findVertex(source); // Get the vertex of our source
        Vertex<Agua> *end_vertex = global_graph.findVertex(sink); // Get the vertex of our sink

        std::queue<Vertex<Agua> *> q; // Initialize the queue

        while (true)
        {
            q.push(start_vertex);

            std::unordered_map<Vertex<Agua>*, Vertex<Agua>*> parent_map; // Map to store parent vertices
            parent_map[start_vertex] = nullptr; // Set parent of source to nullptr

            while (!q.empty())
            {
                Vertex<Agua>* current = q.front();
                q.pop();

                if (current == end_vertex)
                {
                    std::vector<Vertex<Agua>*> augmenting_path;
                    Vertex<Agua>* node = end_vertex;

                    // Reconstruct the augmenting path by backtracking through the parent vertices
                    while (node != nullptr)
                    {
                        augmenting_path.push_back(node);
                        node = parent_map[node];
                    }

                    // Calculate the bottleneck capacity of the augmenting path
                    int bottleneck_capacity = INT_MAX;
                    for (size_t i = 1; i < augmenting_path.size(); ++i)
                    {
                        Edge<Agua>* edge = global_graph.findEdge(augmenting_path[i]->getInfo(), augmenting_path[i - 1]->getInfo());

                        if (edge)
                        {
                            bottleneck_capacity = std::min(bottleneck_capacity, edge->getWeight().get_capacity());
                        }
                        else
                        {
                            std::cout << "Edge was not found in Edmonds-Karp function - searching for min value" << std::endl << std::endl;
                        }
                    }

                    // Update the capacities of edges along the augmenting path
                    for (size_t i = 1; i < augmenting_path.size(); ++i)
                    {
                        Edge<Agua>* edge = global_graph.findEdge(augmenting_path[i]->getInfo(), augmenting_path[i - 1]->getInfo());

                        if (edge)
                        {
                            edge->getWeight().set_capacity(edge->getWeight().get_capacity() - bottleneck_capacity);
                            Pipe new_pipe = edge->getWeight();
                            new_pipe.set_capacity(edge->getWeight().get_capacity() - bottleneck_capacity);
                            edge->setWeight(new_pipe);

                        }
                        else
                        {
                            std::cout << "Edge was not found in Edmonds-Karp function - updating capacity" << std::endl << std::endl;
                        }
                    }

                    max_flow += bottleneck_capacity;
                    break; //sair do loop porque encontramos um augmentation path
                }


                for (Edge<Agua>& edge : current->getAdj())
                {
                    Vertex<Agua>* neighbour = edge.getDest();

                    //check se o proximo que vamos visitar e possivel de visitar, ou seja, capacity positiva e ainda n foi visitado
                    if ((!neighbour->isVisited()) && (edge.getWeight().get_capacity() > 0))
                    {
                        q.push(neighbour);
                        neighbour->setVisited(true);
                        parent_map[neighbour] = current; // Update the parent map
                    }
                }
            }

            // se a queue estiver vazia nao ha mais augmentation paths
            if (q.empty())
            {
                break;
            }

            // reset aos vertexes visitados
            global_graph.set_all_unvisited(global_graph.getVertexSet());
            while (!q.empty())
            {
                q.pop();
            }
        }

        return max_flow;
    }
}


int full_edmonds_karp(std::string city, WMSGraph global_graph)
{
    int max_flow = 0;
    WMSGraph dumy = global_graph;

    std::vector<Agua> sorces = global_graph.get_all_sources(city);

    for(auto& sorce : sorces)
    {
        std::string reservoir = global_graph.get_water_reservoir_code(sorce).get_reservoir();

        max_flow += edmonds_karp(city, reservoir, dumy );

    }

    return max_flow;

}

#endif //DAPROJ_V1_TAREFAS_H
