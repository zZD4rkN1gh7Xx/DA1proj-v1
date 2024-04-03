//
// Created by Administrador on 20/03/2024.
//

#include "pumpingStations.h"

PumpingStation::PumpingStation(int pumping_station_id, std::string pumping_station_code) : Agua(pumping_station_id, pumping_station_code)
{
    this->pumping_station_code = pumping_station_code;
    this->pumping_station_id = pumping_station_id;
}

PumpingStation::PumpingStation(void)
{
    this->pumping_station_id = 0;
    this->pumping_station_code = '0';
}
