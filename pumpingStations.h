//
// Created by Administrador on 20/03/2024.
//

#ifndef DAPROJ1_PUMPINGSTATIONS_H
#define DAPROJ1_PUMPINGSTATIONS_H

#include <iostream>

class PumpingStations {

    private:

        int pumping_station_id;
        std::string pumping_station_code;

    public:

        PumpingStations(int pumping_station_id, std::string pumping_station_code);
        PumpingStations(void);
        int get_pumping_station_id(void);
        std::string get_pumping_station_code(void);

};


#endif //DAPROJ1_PUMPINGSTATIONS_H
