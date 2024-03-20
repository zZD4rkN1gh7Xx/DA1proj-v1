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


class WMSGraph : public virtual Graph<DeliverySite>, public virtual Graph<PumpingStation>, public virtual Graph<WaterReservoir>{

    public:

        void add_delivery_site(DeliverySite& delivery_site);
        void remove_delivery_site(DeliverySite& delivery_site);
        void add_pumping_station(PumpingStation& pumping_station);
        void remove_pumping_station(PumpingStation& pumping_station);
        void add_water_reservoir(WaterReservoir& water_reservoir);
        void remove_water_reservoir(WaterReservoir& water_reservoir);
        void add_pipe(Pipe& pipe);
        void remove_pipe(Pipe& pipe);

        using Graph<DeliverySite>::addVertex;
        using Graph<PumpingStation>::addVertex;
        using Graph<WaterReservoir>::addVertex;

};


#endif //DAPROJ1_WMSGRAPH_H
