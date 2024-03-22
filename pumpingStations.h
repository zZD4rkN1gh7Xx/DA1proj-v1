//
// Created by Administrador on 20/03/2024.
//

#ifndef DAPROJ1_PUMPINGSTATIONS_H
#define DAPROJ1_PUMPINGSTATIONS_H

#include <iostream>
#include <string>
#include "agua.h"

class PumpingStation : public Agua{

    private:

        int pumping_station_id;
        std::string pumping_station_code;

    public:

        PumpingStation(int pumping_station_id, std::string pumping_station_code);
        PumpingStation(void);


};


#endif //DAPROJ1_PUMPINGSTATIONS_H
