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
            if (d.getWeight().get_direction() == 2) {
                continue;
            }
            else {
                cout << d.getWeight().get_code_A() << " goes to " << d.getWeight().get_code_B()
                     << " with a maximum capacity of: " << d.getWeight().get_capacity() << ".";
                sum++;
                if (d.getWeight().get_direction() == 0) {
                    cout << " The pipe goes both ways." << endl;
                } else {
                    cout << endl;
                }
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

void GraphTester::testPipesRemoval() {
    cout << endl << endl;
    bool success1 = true;
    bool success2 = true;
    bool success3 = true;
    bool didDir1 = false;
    bool didDir2 = false;
    Pipe getback1;
    Pipe getback2;
    Pipe getback3;
    string temp1;
    string temp2;
    while (didDir1 == false || didDir2 == false) {
        for (auto a: tt_graph.getVertexSet()) {
            for (auto b: a->getAdj()) {

                if (b.getWeight().get_direction() == 1 && didDir1 == false) {
                    cout << "Testing removal of normal pipe " << b.getWeight().get_code_A() << " - "
                         << b.getWeight().get_code_B() << "..." << endl;
                    temp1 = b.getWeight().get_code_B();
                    getback1 = b.getWeight();
                    tt_graph.remove_pipe(b.getWeight());

                    for (auto c: a->getAdj()) {

                        if (c.getWeight().get_code_B() == temp1) {
                            cout << "Pipe " << c.getWeight().get_code_A() << " - "
                                 << temp1 << " was NOT removed!" << endl << endl;
                            success1 = false;

                        } else
                            continue;
                    }
                    didDir1 = true;
                }
                if (b.getWeight().get_direction() == 0 && didDir2 == false) {
                    cout << "Testing removal of bidirectional pipe " << b.getWeight().get_code_A() << " - "
                         << b.getWeight().get_code_B() << "..." << endl << endl;
                    temp1 = b.getWeight().get_code_B();
                    temp2 = b.getWeight().get_code_A();
                    getback2 = b.getWeight();
                    getback3 = Pipe(b.getWeight().get_code_B(), b.getWeight().get_code_A(), b.getWeight().get_capacity(), 2);
                    tt_graph.remove_pipe(b.getWeight());

                    for (auto c : a->getAdj()) {

                        if (c.getWeight().get_code_B() == temp1) {
                            cout << "Edge " << c.getWeight().get_code_A() << " - "
                                 << temp1 << " was NOT removed!" << endl << endl;
                            success2 = false;
                            break;

                        } else
                            continue;
                    }
                    for (auto f : b.getDest()->getAdj()) {

                        if (f.getWeight().get_code_B() == temp2) {
                            cout << "Inverse edge " << temp2 << " - "
                                 << temp1 << " was NOT removed!" << endl << endl;
                            success3 = false;
                            break;
                        }
                        else
                            continue;
                    }
                    didDir2 = true;

                }
            }
        }
    }
    if (success1 && success2 && success3) {
        cout << "All indicated pipes were removed successfully!" << endl << endl << "Removed pipes were added back." << endl << endl;
    }
    else {
        cout << "One or more pipes were NOT removed completely." << endl << endl << "Removed pipes were added back." << endl << endl;
    }
    if (success1) {
        tt_graph.add_pipe(getback1);
    }
    if (success2) {
        tt_graph.add_pipe(getback2);
    }
    if (success3) {
        tt_graph.add_pipe(getback3);
    }

}
