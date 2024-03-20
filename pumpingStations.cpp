//
// Created by Administrador on 20/03/2024.
//

#include "pumpingStations.h"

PumpingStations::PumpingStations(int pumping_station_id, std::string pumping_station_code)
{
    this->pumping_station_id = pumping_station_id;
    this->pumping_station_code = pumping_station_code;
}

int PumpingStations::get_pumping_station_id(void)
{
    return this->pumping_station_id;
}

std::string PumpingStations::get_pumping_station_code(void)
{
    return this->pumping_station_code;
}