//
// Created by Administrador on 20/03/2024.
//

#include "WMSGraph.h"

void WMSGraph::add_delivery_site(DeliverySite& delivery_site)
{
    addVertex(delivery_site);
}
void add_pumping_station(PumpingStation& pumping_station);
void add_water_reservoir(WaterReservoir& water_reservoir);
void remove_delivery_site(DeliverySite& delivery_site);
void remove_pumping_station(PumpingStation& pumping_station);
void remove_water_reservoir(WaterReservoir& water_reservoir);