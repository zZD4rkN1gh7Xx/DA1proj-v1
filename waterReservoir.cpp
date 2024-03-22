//
// Created by Administrador on 20/03/2024.
//

#include "waterReservoir.h"

WaterReservoir::WaterReservoir(std::string reservoir, std::string municipality, int reservoir_id, std::string reservoid_code, int max_delivery) : Agua(reservoir_id,reservoid_code)
{
    this->reservoir = reservoir;
    this->municipality = municipality;
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

int WaterReservoir::get_max_delivery(void)
{
    return this->max_delivery;
}
