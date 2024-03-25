//
// Created by jogos on 3/23/2024.
//

#ifndef DA1PROJ_V1_GRAPHTESTER_H
#define DA1PROJ_V1_GRAPHTESTER_H

#include "WMSGraph.h"
#include "Graph.h"

class GraphTester {
    WMSGraph tt_graph;

    public:
        GraphTester(WMSGraph tt_graph);
        void testVertexes(void);
        void testPipes(void);
        void testAguaPoints(void);
        void testPipesRemoval(void);

};

#endif //DA1PROJ_V1_GRAPHTESTER_H
