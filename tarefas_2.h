//
// Created by Asus on 31/03/2024.
//

#ifndef PROJDAV1_TAREFAS_2_H
#define PROJDAV1_TAREFAS_2_H

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

            while(child != reservoir->getInfo().get_code())
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
            neighbour.getDest()->setVisited(true);
            parents[neighbour.getDest()->getInfo().get_code()] = current->getInfo().get_code();
            q.push(neighbour.getDest());
        }
    }

    return path;
}

queue<Vertex<Agua> * > get_possible_cities(WMSGraph global_graph, Vertex<Agua>* reservoir)
{
    global_graph.set_all_unvisited(global_graph.getVertexSet());
    queue<Vertex<Agua> * > q;
    queue<Vertex<Agua> * > cities;

    q.push(reservoir);

    while(!q.empty())
    {
        auto current = q.front();
        q.pop();

        if(current->getInfo().get_code()[0] == 'C')
        {
            cities.push(current);
        }

        for(auto neighbour : current->getAdj())
        {
            neighbour.getDest()->setVisited(true);
            q.push(neighbour.getDest());
        }
    }

    return cities;
}

std::unordered_map<int, int> status_inicializator(WMSGraph global_graph)
{
    std::unordered_map<int, int> status;

    for(auto city : global_graph.get_agua_city())
    {
        status[city.second.get_id()] = 0;
    }

    return status;
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

std::unordered_map<std::string, int> giving_initializator(WMSGraph global_graph)
{
    std::unordered_map<std::string, int> giving;

    for(auto agua_point : global_graph.get_aguapoints())
    {
        if(agua_point.first[0] != 'C')
        {
            if(agua_point.first[0] == 'R')
            {
                giving[agua_point.first] = global_graph.get_water_reservoir_code(agua_point.second).get_max_delivery();
            }

            giving[agua_point.first] = 0;
        }
    }

    return giving;
}

int get_total_cap(Vertex<Agua>* pumping_station, WMSGraph shadow_graph, std::unordered_map<int, int> giving)
{
    int total = 0;

    auto a = shadow_graph.findVertex(pumping_station->getInfo());

    for(auto b : a->getAdj())
    {
        total += giving[b.getWeight().get_id()];
    }

    return total;
}

bool is_done(std::unordered_map<int, int> status)
{
    int i = 0;
    int j = status.size();

    for(auto city : status)
    {
        if(city.second == 1 || city.second == 2)
            i++;
    }

    if(i == j)
        return true;

    return false;

}

void back_track(WMSGraph& global_graph  ,WMSGraph shadow_graph, vector<std::string> path, std::unordered_map<std::string, int>& giving,std::unordered_map<int, int>& carry )
{
    vector<std::string> reverse_path = path;

    std::reverse(reverse_path.begin(), reverse_path.end());

    auto needed_pipe = global_graph.findEdge(global_graph.get_agua_point(path[1]),global_graph.get_agua_point(path[0]));

    int receives = carry[needed_pipe->getWeight().get_id()];

    int exceeds = receives - global_graph.get_agua_city_code(global_graph.get_agua_point(reverse_path[0])).get_demand();

    for(auto it = reverse_path.begin() + 1; it != reverse_path.end(); it++)
    {
        auto edge = global_graph.findEdge(global_graph.get_agua_point(*it), global_graph.get_agua_point(*(it - 1)));
        carry[edge->getWeight().get_id()] -= exceeds;
        giving[*it] -= exceeds;
    }

}

int fill_city(WMSGraph global_graph,std::unordered_map<int, int>& carry, std::unordered_map<std::string, int>& giving, vector<std::string> city_path)
{
    auto current_reservoir = global_graph.get_water_reservoir_code(global_graph.get_agua_point(city_path[0]));

    for(auto it = city_path.begin(); it != city_path.end() - 1; it++)
    {
        auto current_edge = global_graph.findEdge(global_graph.get_agua_point(*it),global_graph.get_agua_point(*(it +1)) );
        auto next_point = global_graph.findVertex(global_graph.get_agua_point(*(it + 1)));

        if(giving[current_reservoir.get_code()] > 0)
        {
           auto fill = current_edge->getWeight().get_capacity() - carry[current_edge->getWeight().get_id()];

           if(giving[current_reservoir.get_code()] >= fill)
           {
                giving[current_reservoir.get_code()] -= fill;
                carry[current_edge->getWeight().get_id()] += fill;
                giving[next_point->getInfo().get_code()] += fill;
           }
           else
           {
                giving[current_reservoir.get_code()] = 0;
                carry[current_edge->getWeight().get_id()] += giving[current_reservoir.get_code()] ;
                giving[next_point->getInfo().get_code()] += giving[current_reservoir.get_code()];
           }
        }
    }
}

void is_it_enough(WMSGraph& global_graph, WMSGraph shadow_graph) {
    std::unordered_map<int, int> carry; // What each pipe will be able to give ( max at pipe capacity)
    std::unordered_map<std::string, int> giving; // what each pipe will be giving out
    std::unordered_map<int, bool> full;
    std::unordered_map<int, int> status; // status of the water 0: to be processed, 1: processed, more water than nedded received, 2: unavailable(gitting the limit wanted), -1 being processed
    std::unordered_map<std::string, queue<Vertex<Agua> * >> reservoirs_cities;
    std::queue<Vertex<Agua> *> reservoir_queue;

    for(auto reservoir : global_graph.get_agua_reservoir()) // inicaliazdor das cidades que cada reservatoio chega
    {
        reservoirs_cities[reservoir.second.get_code()] = get_possible_cities(global_graph, global_graph.findVertex(reservoir.second));
        reservoir_queue.push(global_graph.findVertex(reservoir.second));
    }

    status = status_inicializator(global_graph);
    carry = carry_initializator(global_graph);
    giving = giving_initializator(global_graph);

    // a condiçao de paragem vai ser ou quando estiverem todos tratados , ou todos indisponiveis ou quando nao houver reservatiorios na queue

    while(!is_done(status) || !reservoir_queue.empty())
    {
        auto current_reservoir = reservoir_queue.front();
        reservoir_queue.pop();

        auto city = reservoirs_cities[current_reservoir->getInfo().get_code()].front();

        if(status[city->getInfo().get_id()] == 2)
            reservoirs_cities[current_reservoir->getInfo().get_code()].pop();

        else
        {
            if(status[city->getInfo().get_id()] == 0)
            {
                vector<std::string> path = get_city_path(global_graph, current_reservoir, city);
                fill_city(global_graph, carry, giving, path);

                if(giving[city->getInfo().get_code()] > global_graph.get_agua_city_code(city->getInfo()).get_demand())
                {
                    status[global_graph.get_agua_city_code(city->getInfo()).get_id()] = 1;
                    reservoirs_cities[current_reservoir->getInfo().get_code()].push(city);
                }

                if(giving[city->getInfo().get_code()] < global_graph.get_agua_city_code(city->getInfo()).get_demand())
                {
                    status[global_graph.get_agua_city_code(city->getInfo()).get_id()] = -1;
                    reservoirs_cities[current_reservoir->getInfo().get_code()].push(city);
                }

                if(giving[city->getInfo().get_code()] < global_graph.get_agua_city_code(city->getInfo()).get_demand())
                {
                    status[global_graph.get_agua_city_code(city->getInfo()).get_id()] = 2;

            }   }
        }




        if(giving[current_reservoir->getInfo().get_code()] < global_graph.get_water_reservoir_code(current_reservoir->getInfo()).get_max_delivery())
            reservoir_queue.push(current_reservoir);

    }

}








#endif //PROJDAV1_TAREFAS_2_H
