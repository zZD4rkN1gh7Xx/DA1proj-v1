//
// Created by Administrador on 20/03/2024.
//

#ifndef DAPROJ1_WMSGRAPH_H
#define DAPROJ1_WMSGRAPH_H

#include "Graph.h"
#include "deliverySites.h"
#include "pumpingStations.h"
#include "waterReservoir.h"
#include "Pipes.h"
#include "agua.h"


class WMSGraph : Graph<Agua>{

    public:

        void add_delivery_site(DeliverySite& delivery_site);
        void add_pumping_station(PumpingStation& pumping_station);
        void add_water_reservoir(WaterReservoir& water_reservoir);
        void remove_delivery_site(DeliverySite& delivery_site);
        void remove_pumping_station(PumpingStation& pumping_station);
        void remove_water_reservoir(WaterReservoir& water_reservoir);

};


#endif //DAPROJ1_WMSGRAPH_H
