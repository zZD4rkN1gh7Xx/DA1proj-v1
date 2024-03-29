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
#include <unordered_set>

int get_total_cap(Vertex<Agua>* pumping_station, WMSGraph shadow_graph, std::unordered_map<int, int> giving)
{
    int total = 0;

    auto a = shadow_graph.findVertex(pumping_station->getInfo());

    for(auto b : a->getAdj())
    {
        if(giving.count(b.getWeight().get_id()) == 0)
            return -1;

        else
        {
            total += giving[b.getWeight().get_id()];
        }
    }

    return total;
}




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

//Fazer os couts no menu.
int full_edmonds_karp(std::string city, WMSGraph global_graph, WMSGraph shadow_graph)  //e no shadow que se vai buscar
{
    int max_flow = 0;
    WMSGraph dumy = global_graph;

    std::vector<Agua> sorces = shadow_graph.get_all_sources(city);

    for(auto& sorce : sorces)
    {
        std::string reservoir = global_graph.get_water_reservoir_code(sorce).get_reservoir();

        max_flow += edmonds_karp(city, reservoir, dumy );

    }

    return max_flow;

}

//A CAPACIDADE DOS PIPES N INTERESSA NO CODIGO
//SO O PRIMEIRO PIPE ALTERA A AGUA QUE PASSA POR TODOS

//O PIPE 1 APARECE QUE N LEVA AGUA?
//O ULTIMO PIPE APARECE QUE N LEVA AGUA TAMBEM

//NO GRAFO GRANDE 2 PIPES N APARECEM PORQUE O DESTINO DELES JA FOI VISITADO APARENTEMENTE
//O CHATGPT TINHA ARRANJADO ISSO AO FAZER COM QUE OS VERTICES JA VISITADOS ESTIVESSEM NO UNORDERED_SET "visited"
//VOU DEIXAR AQUI EM BAIXO O CODIGO QUE ELE ME DEU MAS QUE DA VALOR NEGATIVO NO PIPE 4:

/* std::unordered_map<int, int> is_it_enough(WMSGraph global_graph) {
    std::unordered_map<int, int> carry; // What each pipe will carry
    std::unordered_map<int, int> giving;
    std::queue<Vertex<Agua>*> q;
    global_graph.set_all_unvisited(global_graph.getVertexSet());

    for (auto& source : global_graph.get_agua_reservoir()) {
        std::unordered_set<Vertex<Agua>*> visited; // Track visited vertices for each source
        Vertex<Agua>* current_source = global_graph.findVertex(source.second);

        if (current_source == nullptr) {
            std::cout << "source was not found in is_it_enough func" << std::endl;
            continue;
        }

        int flow = global_graph.get_water_reservoir_code(current_source->getInfo()).get_max_delivery();
        q.push(current_source);

        while (!q.empty()) {
            Vertex<Agua>* current = q.front();
            q.pop();

            visited.insert(current); // Mark current vertex as visited

            for (auto& pipe : current->getAdj()) {
                Vertex<Agua>* neighbour = pipe.getDest();

                // Skip the neighbor if it's already in the set of visited vertices
                if (visited.find(neighbour) != visited.end()) {
                    continue;
                }

                if (carry.count(pipe.getWeight().get_id()) == 0) {
                    carry[pipe.getWeight().get_id()] = 0;
                    giving[pipe.getWeight().get_id()] = 0;
                }

                if (current->getInfo().get_code()[0] == 'R') {
                    int capacity = pipe.getWeight().get_capacity();
                    if (flow >= capacity) {
                        carry[pipe.getWeight().get_id()] = capacity;
                        flow -= capacity;
                    } else {
                        carry[pipe.getWeight().get_id()] = flow;
                        flow = 0;
                    }
                } else if (current->getInfo().get_code()[0] == 'P') {
                    if (carry.count(pipe.getWeight().get_id()) == 0) {
                        carry[pipe.getWeight().get_id()] = 0;
                        giving[pipe.getWeight().get_id()] = 0;
                    }
                    giving[pipe.getWeight().get_id()] = carry[current->getInfo().get_id()] - giving[current->getInfo().get_id()];
                }

                // Push the neighbor to the queue for further exploration
                q.push(neighbour);
            }
        }
    }

    return giving; // Return the giving map according to function name
}
*/





/*
 std::unordered_map<int, int> is_it_enough(WMSGraph global_graph) {
    std::unordered_map<int, int> carry; // What each pipe will carry
    std::unordered_map<int, int> giving;
    std::queue<Vertex<Agua>*> q;
    global_graph.set_all_unvisited(global_graph.getVertexSet());

    for (auto& source : global_graph.get_agua_reservoir()) {
        global_graph.set_all_unvisited(global_graph.getVertexSet());

        Vertex<Agua>* current_source = global_graph.findVertex(source.second);

        if (current_source == nullptr) {
            std::cout << "source was not found in is_it_enough func" << std::endl;
            continue;
        }

        int flow = global_graph.get_water_reservoir_code(current_source->getInfo()).get_max_delivery();
        q.push(current_source);

        std::unordered_set<Vertex<Agua>*> visited; // Keep track of visited vertices

        while (!q.empty()) {
            Vertex<Agua>* current = q.front();
            q.pop();

            visited.insert(current); // Mark current vertex as visited

            for (auto& pipe : current->getAdj()) {
                Vertex<Agua>* neighbour = pipe.getDest();

                if (pipe.getWeight().get_id() == 22 || pipe.getWeight().get_id() == 32) {
                    cout << endl << endl << pipe.getWeight().get_code_A() << " - " << pipe.getWeight().get_code_B() << endl << endl;
                }

                if (current->getInfo().get_code()[0] == 'R') {
                    if (carry.count(pipe.getWeight().get_id()) == 0) {
                        carry[pipe.getWeight().get_id()] = 0;
                        giving[pipe.getWeight().get_id()] = 0;
                    }

                    if (visited.find(neighbour) == visited.end()) { // Check if neighbour has been visited
                        q.push(neighbour);
                        visited.insert(neighbour); // Mark neighbour vertex as visited
                    }

                    int capacity = pipe.getWeight().get_capacity();

                    if (flow >= capacity) {
                        carry[pipe.getWeight().get_id()] = capacity;
                        flow -= capacity;
                    }
                    else {
                        carry[pipe.getWeight().get_id()] = flow;
                        flow = 0;
                    }
                }
                else if (current->getInfo().get_code()[0] == 'P') {
                    if (visited.find(neighbour) == visited.end()) { // Check if neighbour has been visited
                        q.push(neighbour);
                        visited.insert(neighbour); // Mark neighbour vertex as visited
                    }

                    if (carry.count(pipe.getWeight().get_id()) == 0) {
                        carry[pipe.getWeight().get_id()] = 0;
                        giving[pipe.getWeight().get_id()] = 0;

                        if (giving[current->getInfo().get_id()] < carry[current->getInfo().get_id()]) {
                            giving[pipe.getWeight().get_id()] = carry[current->getInfo().get_id()] - giving[current->getInfo().get_id()];
                        }
                    }

                    if (giving[current->getInfo().get_id()] < carry[current->getInfo().get_id()]) {
                        giving[pipe.getWeight().get_id()] = carry[current->getInfo().get_id()] - giving[current->getInfo().get_id()];
                    }
                }
            }
        }
    }

    return giving; // Return the giving map according to function name
}

//greedy algorithm, // nao precisamos de usar status de visited ja que dps vamos querer voltar a ele e atualiza lo
/*std::unordered_map<int, int> is_it_enough(WMSGraph global_graph) {
    std::unordered_map<int, int> carry; // What each pipe will carry
    std::unordered_map<int, int> giving;
    std::queue<Vertex<Agua>*> q;
    global_graph.set_all_unvisited(global_graph.getVertexSet());

    for (auto& source : global_graph.get_agua_reservoir()) {
        global_graph.set_all_unvisited(global_graph.getVertexSet());

        Vertex<Agua>* current_source = global_graph.findVertex(source.second);

        if (current_source == nullptr) {
            std::cout << "source was not found in is_it_enough func" << std::endl;
            continue;
        }

        int flow = global_graph.get_water_reservoir_code(current_source->getInfo()).get_max_delivery();
        q.push(current_source);

        // Set the visited status of the source vertex when pushed into the queue
        current_source->setVisited(true);

        while (!q.empty()) {
            Vertex<Agua>* current = q.front();
            q.pop();

            // current->setVisited(true); // Remove this line

            for (auto& pipe : current->getAdj()) {
                Vertex<Agua>* neighbour = pipe.getDest();

                if (pipe.getWeight().get_id() == 22 || pipe.getWeight().get_id() == 32) {
                    cout << endl << endl << pipe.getWeight().get_code_A() << " - " << pipe.getWeight().get_code_B() << endl << endl;
                }
                if (!neighbour->isVisited()) {
                    if (current->getInfo().get_code()[0] == 'R') {
                        if (carry.count(pipe.getWeight().get_id()) == 0) {
                            carry[pipe.getWeight().get_id()] = 0;
                            giving[pipe.getWeight().get_id()] = 0;
                        }

                        q.push(neighbour);

                        int capacity = pipe.getWeight().get_capacity();

                        if (flow >= capacity) {
                            carry[pipe.getWeight().get_id()] = capacity;
                            giving[pipe.getWeight().get_id()] = capacity;
                            flow -= capacity;
                        }
                        else {
                            carry[pipe.getWeight().get_id()] = flow;
                            giving[pipe.getWeight().get_id()] = flow;
                            flow = 0;
                        }
                    }
                    else if (current->getInfo().get_code()[0] == 'P') {
                        q.push(neighbour);

                        if (carry.count(pipe.getWeight().get_id()) == 0) {
                            carry[pipe.getWeight().get_id()] = 0;
                            giving[pipe.getWeight().get_id()] = 0;

                            if (giving[current->getInfo().get_id()] < carry[current->getInfo().get_id()]) {
                                giving[pipe.getWeight().get_id()] = carry[current->getInfo().get_id()] - giving[current->getInfo().get_id()];
                            }

                        }

                        if (giving[current->getInfo().get_id()] < carry[current->getInfo().get_id()]) {
                            giving[pipe.getWeight().get_id()] = carry[current->getInfo().get_id()] - giving[current->getInfo().get_id()];
                        }
                    }
                    // Mark neighbour vertex as visited
                    neighbour->setVisited(true);
                }
            }
        }
    }

    return giving; // Return the giving map according to function name
}
*/

void is_it_enough(WMSGraph global_graph, WMSGraph shadow_graph) {
    std::unordered_map<int, int> carry; // What each pipe will be able to give ( max at pipe capacity)
    std::unordered_map<int, int> giving; // what each pipe will be giving out
    std::unordered_map<int, bool> visited;
    std::queue<Vertex<Agua> *> q;

    while(visited.size() < global_graph.get_total_num_of_edges()) // para termos a certeza a que fomos a todas as edges
    {
        for(auto& source : global_graph.get_agua_reservoir())
        {
            Vertex<Agua>* current_source = global_graph.findVertex(source.second);

            if (current_source == nullptr) {
                std::cout << "source was not found in is_it_enough func" << std::endl;
                continue;
            }

            int flow = global_graph.get_water_reservoir_code(current_source->getInfo()).get_max_delivery();
            q.push(current_source);

            while(!q.empty())
            {
                Vertex<Agua>* current = q.front();

                q.pop();
                int delivery = get_total_cap(current,shadow_graph, giving );
                for (auto& pipe : current->getAdj())
                {
                    Vertex<Agua>* neighbour = pipe.getDest();

                    if(visited.count(pipe.getWeight().get_id()) == 0)
                    {
                        visited[pipe.getWeight().get_id()] = true;
                    }

                    if(current->getInfo().get_code()[0] == 'R')
                    {
                        if (carry.count(pipe.getWeight().get_id()) == 0) {
                            carry[pipe.getWeight().get_id()] = 0;
                            giving[pipe.getWeight().get_id()] = 0;
                        }

                        q.push(neighbour);

                        int capacity = pipe.getWeight().get_capacity();

                        if (flow >= capacity) {
                            carry[pipe.getWeight().get_id()] = capacity;
                            giving[pipe.getWeight().get_id()] = capacity;
                            flow -= capacity;
                        }

                        else if (flow < capacity)
                        {
                            carry[pipe.getWeight().get_id()] = flow;
                            giving[pipe.getWeight().get_id()] = flow;
                            flow = 0;
                        }
                    }

                    else if(current->getInfo().get_code()[0] == 'P')
                    {
                        q.push(neighbour);

                        int capacity = pipe.getWeight().get_capacity();

                        if(delivery == -1)
                            continue;

                        if (delivery >= capacity) {

                            carry[pipe.getWeight().get_id()] = capacity;
                            giving[pipe.getWeight().get_id()] = capacity;
                            delivery -= capacity;
                        }

                        else if (delivery < capacity)
                        {
                            carry[pipe.getWeight().get_id()] = delivery;
                            giving[pipe.getWeight().get_id()] = delivery;
                            delivery = 0;
                        }
                    }

                    else if (current->getInfo().get_code()[0] == 'C')
                    {
                        int receives = get_total_cap(current, shadow_graph, giving);

                        if(receives == -1)
                            continue;

                        std::cout << "the city " << current->getInfo().get_code() << " receives " << receives << std::endl;
                    }
                }
            }
        }
    }
}










#endif //DAPROJ_V1_TAREFAS_H
