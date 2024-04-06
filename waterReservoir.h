//
// Created by Administrador on 20/03/2024.
//

/**

    *@file waterReservoir.h
    *@brief Header file for the WaterReservoir class an extention of the Agua class
*/

#ifndef DAPROJ1_WATERRESERVOIR_H
#define DAPROJ1_WATERRESERVOIR_H

#include <string>
#include "agua.h"


class WaterReservoir : public Agua{

    private:

        std::string reservoir;
        std::string municipality;
        std::string reservoir_code;
        int reservoir_id;
        int max_delivery;

    public:

        WaterReservoir(std::string reservoir, std::string municipality, int reservoir_id, std::string reservoir_code, int max_delivery);
        WaterReservoir(void);
        std::string get_reservoir(void);
        std::string get_municipality(void);
        int get_reservoi_id(void);
        int get_max_delivery(void);
        void set_max_delivery(int max_delivery);

};


#endif //DAPROJ1_WATERRESERVOIR_H
