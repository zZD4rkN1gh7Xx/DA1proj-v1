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
#include <climits>

void status_checker(WMSGraph global_graph, Vertex<Agua> *city ,unordered_map<std::string, int>& giving, unordered_map<std::string, vector<std::string>> &path_saver, unordered_map<int, int> &status, vector<std::string> path) {
    if(giving[city->getInfo().get_code()] > global_graph.get_agua_city_code(city->getInfo()).get_demand())
    {
        status[global_graph.get_agua_city_code(city->getInfo()).get_id()] = 1;
        path_saver[city->getInfo().get_code()] = path;
    }

    if(giving[city->getInfo().get_code()] < global_graph.get_agua_city_code(city->getInfo()).get_demand())
    {
        status[global_graph.get_agua_city_code(city->getInfo()).get_id()] = -1;
    }

    if(giving[city->getInfo().get_code()] == global_graph.get_agua_city_code(city->getInfo()).get_demand())
    {
        status[global_graph.get_agua_city_code(city->getInfo()).get_id()] = 2;
    }
}

Vertex<Agua> *get_available_city(std::queue<Vertex<Agua> *> reservoir_queue, std::unordered_map<int, int> status)
{

    while (!reservoir_queue.empty()) {
        auto current = reservoir_queue.front();
        reservoir_queue.pop();

        if (status[current->getInfo().get_id()] == 1) {
            return current;
        }

    }
    return nullptr;
}

vector<std::string> get_city_path(WMSGraph global_graph, Vertex<Agua>* reservoir, Vertex<Agua> * city, std::unordered_map<int, bool> full)
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

            while(parents[child] != reservoir->getInfo().get_code())                   //se fosse child != como estava ficava um valor "" no vetor path
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
            if (!full[neighbour.getWeight().get_id()] && !neighbour.getDest()->isVisited()) {    // fazia ciclo infinito, ver se continua certo
                neighbour.getDest()->setVisited(true);
                parents[neighbour.getDest()->getInfo().get_code()] = current->getInfo().get_code();
                q.push(neighbour.getDest());
            }
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
            if (!neighbour.getDest()->isVisited()) {
                neighbour.getDest()->setVisited(true);
                q.push(neighbour.getDest());
            }
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

            else {
                giving[agua_point.first] = 0;
            }
        }
        else {
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

void back_track(WMSGraph& global_graph  ,WMSGraph shadow_graph, vector<std::string> path, std::unordered_map<std::string, int>& giving,std::unordered_map<int, int>& carry, std::unordered_map<int, bool>& full, std::unordered_map<int, int>& status)
{

    vector<std::string> reverse_path = path;

    std::reverse(reverse_path.begin(), reverse_path.end());

    auto needed_pipe = global_graph.findEdge(global_graph.get_agua_point(reverse_path[1]),global_graph.get_agua_point(reverse_path[0]));

    int exceeds = giving [*reverse_path.begin()] - global_graph.get_agua_city_code(global_graph.get_agua_point(reverse_path[0])).get_demand();

    giving[*reverse_path.begin()] -= exceeds;

    for(auto it = reverse_path.begin() + 1; it != reverse_path.end(); it++)
    {
        auto edge = global_graph.findEdge(global_graph.get_agua_point(*it), global_graph.get_agua_point(*(it - 1)));
        full[edge->getWeight().get_id()] = false;
        carry[edge->getWeight().get_id()] -= exceeds;
        giving[*it] += exceeds;
    }

    status[global_graph.get_agua_city_name(reverse_path[0]).get_id()] = 2;

}

void fill_city(WMSGraph global_graph,std::unordered_map<int, int>& carry, std::unordered_map<std::string, int>& giving, vector<std::string> city_path, std::unordered_map<int, bool>& full)
{
    unordered_map<std::string, int> initial_giving;
    unordered_map<std::string, int> starting_giving;

    auto max_flow = INT_MAX;
    auto starting_delivery = 0;
    if (city_path.empty()) {
        cout << "gg" << endl;
    }
    else {

        auto current_reservoir = global_graph.get_water_reservoir_code(global_graph.get_agua_point(city_path[0]));


        for (auto it = city_path.begin(); it != city_path.end() - 1; it++) {
            auto current_edge = global_graph.findEdge(global_graph.get_agua_point(*it),global_graph.get_agua_point(*(it + 1)));

            auto next_point = global_graph.findVertex(global_graph.get_agua_point(*(it + 1)));
            starting_giving[next_point->getInfo().get_code()] = giving[next_point->getInfo().get_code()];

            if (*it == current_reservoir.get_code()) {
                if (giving[current_reservoir.get_code()] > 0) {
                    auto fill = current_edge->getWeight().get_capacity() - carry[current_edge->getWeight().get_id()];

                    if (giving[current_reservoir.get_code()] >= fill) {
                        giving[current_reservoir.get_code()] -= fill;
                        giving[next_point->getInfo().get_code()] += fill;
                        initial_giving[next_point->getInfo().get_code()] = fill;
                        starting_delivery = fill;
                    } else {
                        giving[next_point->getInfo().get_code()] += giving[current_reservoir.get_code()];
                        fill = giving[current_reservoir.get_code()];
                        starting_delivery = giving[current_reservoir.get_code()];
                        initial_giving[next_point->getInfo().get_code()] = giving[current_reservoir.get_code()];
                        giving[current_reservoir.get_code()] = 0;

                    }
                    if (fill < max_flow) max_flow = fill;

                }
            } else {
                auto fill = current_edge->getWeight().get_capacity() - carry[current_edge->getWeight().get_id()];
                if (fill >= giving[*it]) {
                    giving[next_point->getInfo().get_code()] += giving[*it];
                    initial_giving[next_point->getInfo().get_code()] = giving[*it];
                    giving[*it] = 0;
                } else {
                    giving[next_point->getInfo().get_code()] += fill;
                    initial_giving[next_point->getInfo().get_code()] = fill;
                    giving[*it] -= fill;
                }
                if (fill < max_flow) max_flow = fill;

            }

        }
        for (auto it = city_path.begin(); it != city_path.end() - 1; it++) {
            auto current_edge = global_graph.findEdge(global_graph.get_agua_point(*it),global_graph.get_agua_point(*(it + 1)));
            auto next_point = global_graph.findVertex(global_graph.get_agua_point(*(it + 1)));
            carry[current_edge->getWeight().get_id()] += max_flow;
            if (carry[current_edge->getWeight().get_id()] == current_edge->getWeight().get_capacity())
                full[current_edge->getWeight().get_id()] = true;
            if (initial_giving[next_point->getInfo().get_code()] == max_flow)
                giving[next_point->getInfo().get_code()] = starting_giving[next_point->getInfo().get_code()] + max_flow;
            else
                giving[next_point->getInfo().get_code()] = starting_giving[next_point->getInfo().get_code()] + max_flow;
        }
        giving[current_reservoir.get_code()] += (starting_delivery - max_flow);

    }
}

void is_it_enough(WMSGraph& global_graph, WMSGraph shadow_graph) {
    std::unordered_map<int, int> carry; // What each pipe will be able to give ( max at pipe capacity)
    std::unordered_map<std::string, int> giving; // what each pipe will be giving out
    std::unordered_map<int, bool> full;
    std::unordered_map<int, int> status; // status of the water 0: to be processed, 1: processed, more water than nedded received, 2: unavailable(gitting the limit wanted), -1 being processed
    std::unordered_map<std::string, queue<Vertex<Agua> * >> reservoirs_cities;
    std::unordered_map<std::string, vector<std::string>> path_saver;
    std::queue<Vertex<Agua> *> reservoir_queue;
    std::unordered_map<std::string, int> prev_delivery;

    for(auto reservoir : global_graph.get_agua_reservoir()) // inicaliazdor das cidades que cada reservatoio chega
    {
        reservoirs_cities[reservoir.second.get_code()] = get_possible_cities(global_graph, global_graph.findVertex(reservoir.second));
        reservoir_queue.push(global_graph.findVertex(reservoir.second));
    }

    status = status_inicializator(global_graph);
    carry = carry_initializator(global_graph);
    giving = giving_initializator(global_graph);

    // a condiçao de paragem vai ser ou quando estiverem todos tratados , ou todos indisponiveis ou quando nao houver reservatiorios na queue

    while(!is_done(status) && !reservoir_queue.empty())
    {
        auto current_reservoir = reservoir_queue.front();
        reservoir_queue.pop();
        if (reservoirs_cities[current_reservoir->getInfo().get_code()].empty()) {
            continue;
        }
        auto city = reservoirs_cities[current_reservoir->getInfo().get_code()].front();
        reservoirs_cities[current_reservoir->getInfo().get_code()].pop();

        if (city == nullptr) {
            continue;
        }


        if(status[city->getInfo().get_id()] == 2)
            reservoirs_cities[current_reservoir->getInfo().get_code()].pop();

        else
        {
            if(status[city->getInfo().get_id()] == 0)
            {
                vector<std::string> path = get_city_path(global_graph, current_reservoir, city, full);


                if (path.empty()) {
                    auto vertex = get_available_city(reservoirs_cities[current_reservoir->getInfo().get_code()], status);
                    if (vertex == nullptr) {
                        reservoirs_cities[current_reservoir->getInfo().get_code()].pop();
                        continue;
                    }
                    else {
                        back_track(global_graph, shadow_graph, path_saver[vertex->getInfo().get_code()], giving, carry,
                                   full, status);
                        fill_city(global_graph, carry, giving, get_city_path(global_graph, current_reservoir, city, full),
                                  full);
                        continue;
                    }
                }


                fill_city(global_graph, carry, giving, path, full);

                if(giving[city->getInfo().get_code()] > global_graph.get_agua_city_code(city->getInfo()).get_demand())
                {
                    status[global_graph.get_agua_city_code(city->getInfo()).get_id()] = 1;
                    reservoirs_cities[current_reservoir->getInfo().get_code()].push(city);
                    path_saver[city->getInfo().get_code()] = path;
                }

                if(giving[city->getInfo().get_code()] < global_graph.get_agua_city_code(city->getInfo()).get_demand())
                {
                    status[global_graph.get_agua_city_code(city->getInfo()).get_id()] = -1;
                    auto path = get_city_path(global_graph, current_reservoir, city, full);
                    while (!path.empty() && status[global_graph.get_agua_city_code(city->getInfo()).get_id()] == -1) {
                        fill_city(global_graph, carry, giving, path, full);

                        status_checker(global_graph,city, giving, path_saver, status, path);

                        path = get_city_path(global_graph, current_reservoir, city, full);

                    }

                    reservoirs_cities[current_reservoir->getInfo().get_code()].push(city);
                }

                if(giving[city->getInfo().get_code()] == global_graph.get_agua_city_code(city->getInfo()).get_demand())
                {
                    status[global_graph.get_agua_city_code(city->getInfo()).get_id()] = 2;
                }

            }

            if(status[city->getInfo().get_id()] == -1) {
                auto vertex = get_available_city(reservoirs_cities[current_reservoir->getInfo().get_code()], status);
                if (vertex == nullptr)
                    reservoirs_cities[current_reservoir->getInfo().get_code()].pop();
                else {
                    back_track(global_graph, shadow_graph, path_saver[vertex->getInfo().get_code()], giving, carry, full, status);
                    auto path = get_city_path(global_graph, current_reservoir, city, full);
                    fill_city(global_graph, carry, giving, path, full);

                    if(giving[city->getInfo().get_code()] > global_graph.get_agua_city_code(city->getInfo()).get_demand())
                    {
                        status[global_graph.get_agua_city_code(city->getInfo()).get_id()] = 1;
                        reservoirs_cities[current_reservoir->getInfo().get_code()].push(city);
                        path_saver[city->getInfo().get_code()] = path;
                    }

                    if(giving[city->getInfo().get_code()] < global_graph.get_agua_city_code(city->getInfo()).get_demand())
                    {
                        status[global_graph.get_agua_city_code(city->getInfo()).get_id()] = -1;
                        reservoirs_cities[current_reservoir->getInfo().get_code()].push(city);
                    }

                    if(giving[city->getInfo().get_code()] == global_graph.get_agua_city_code(city->getInfo()).get_demand())
                    {
                        status[global_graph.get_agua_city_code(city->getInfo()).get_id()] = 2;
                    }

                }
            }

        }

        if(giving[current_reservoir->getInfo().get_code()] < global_graph.get_water_reservoir_code(current_reservoir->getInfo()).get_max_delivery())

            if (prev_delivery.count(current_reservoir->getInfo().get_code()) == 0) {
                prev_delivery[current_reservoir->getInfo().get_code()] = giving[current_reservoir->getInfo().get_code()];
                reservoir_queue.push(current_reservoir);
            }
            else if (prev_delivery[current_reservoir->getInfo().get_code()] == giving[current_reservoir->getInfo().get_code()]) {
                if (status[global_graph.get_agua_city_code(city->getInfo()).get_id()] == 1) {
                    reservoir_queue.push(current_reservoir);
                    continue;
                }
                continue;
            }
            else {
                prev_delivery[current_reservoir->getInfo().get_code()] = giving[current_reservoir->getInfo().get_code()];
                reservoir_queue.push(current_reservoir);
            }

    }
    for (auto a : global_graph.get_agua_city()) {
        cout << a.first << " gets " << giving[a.first] << endl;
    }

}

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




#endif //PROJDAV1_TAREFAS_2_H
