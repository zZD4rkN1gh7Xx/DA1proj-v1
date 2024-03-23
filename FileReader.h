//
// Created by Administrador on 22/03/2024.
//

#ifndef DAPROJ1_FILEREADER_H
#define DAPROJ1_FILEREADER_H

#include "agua.h"
#include "deliverySites.h"
#include "Pipes.h"
#include "pumpingStations.h"
#include "waterReservoir.h"
#include "WMSGraph.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

class FileReader {

    public:
        static void add_reservoirs(WMSGraph &OurGraph);
        static void add_stations(WMSGraph &OurGraph);
        static void add_cities(WMSGraph &OurGraph);
        static void add_pipes(WMSGraph &OurGraph);

};


#endif //DAPROJ1_FILEREADER_H
