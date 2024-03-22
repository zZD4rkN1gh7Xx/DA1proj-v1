//
// Created by Administrador on 20/03/2024.
//

#include "WMSGraph.h"


void WMSGraph::add_delivery_site(DeliverySite& delivery_site)
{
    addVertex(delivery_site);
}


void WMSGraph::add_pumping_station(PumpingStation& pumping_station)
{
    addVertex(pumping_station);
}

void WMSGraph::add_water_reservoir(WaterReservoir& water_reservoir)
{
    addVertex(water_reservoir);
}

void WMSGraph::remove_delivery_site(DeliverySite& delivery_site)
{
    removeVertex(delivery_site);
}

void WMSGraph::remove_pumping_station(PumpingStation& pumping_station)
{
    removeVertex(pumping_station);
}
void WMSGraph::remove_water_reservoir(WaterReservoir& water_reservoir)
{
    removeVertex(water_reservoir);
}

