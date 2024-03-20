//
// Created by Administrador on 20/03/2024.
//

#include "waterReservoir.h"

WaterReservoir::WaterReservoir(std::string reservoir, std::string municipality, int reservoir_id, int max_delivery)
{
    this->reservoir = reservoir;
    this->municipality = municipality;
    this->reservoir_id = reservoir_id;
    this->max_delivery = max_delivery;
}

std::string WaterReservoir::get_reservoir(void)
{
    return this->reservoir;
}

std::string WaterReservoir::get_municipality(void)
{
    return this->municipality;
}

int WaterReservoir::get_reservoi_id(void)
{
    return this->reservoir_id;
}

int WaterReservoir::get_max_delivery(void)
{
    return this->max_delivery;
}
