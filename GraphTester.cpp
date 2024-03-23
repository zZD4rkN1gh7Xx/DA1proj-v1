//
// Created by jogos on 3/23/2024.
//

#include "GraphTester.h"

GraphTester::GraphTester(WMSGraph tt_graph) {
    this->tt_graph = tt_graph;
}

void GraphTester::testVertexes(void) {
    cout << endl << endl;
    int sum = 0;
    for (auto v : tt_graph.getVertexSet()) {
        cout << "Vertex code: " << v->getInfo().get_code() << " | Vertex id: " << v->getInfo().get_id() << endl;
        sum++;
    }
    cout << endl << "Total vertex count: " << sum;
}

void GraphTester::testPipes(void) {
    cout << endl << endl;
    int sum = 0;
    for (auto a: tt_graph.getVertexSet()) {
        for (auto d : a->getAdj()) {
            cout << d.getWeight().get_code_A() << " goes to " << d.getWeight().get_code_B() << " with a maximum capacity of: " << d.getWeight().get_capacity() << ".";
            sum++;
            if (d.getWeight().get_direction() == 0) {
                cout << " The pipe goes both ways." << endl;
            }
            else {
                cout << endl;
            }
        }
    }
    cout << endl << "Total pipe count: " << sum;
}

void GraphTester::testAguaPoints(void) {
    cout << endl << endl;
    int sum = 0;
    for (auto a : tt_graph.get_aguapoints()) {
        cout << "Vertex " << a.first << " of id " << a.second.get_id() << " is in aguapoints!" << endl;
        sum++;
    }
    cout << endl << "Total aguapoint count: " << sum << endl;
}
