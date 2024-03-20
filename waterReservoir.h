//
// Created by Administrador on 20/03/2024.
//

#ifndef DAPROJ1_WATERRESERVOIR_H
#define DAPROJ1_WATERRESERVOIR_H

#include <string>


class WaterReservoir {

    private:

        std::string reservoir;
        std::string municipality;
        int reservoir_id;
        int max_delivery;

    public:

        WaterReservoir(std::string reservoir, std::string municipality, int reservoir_id, int max_delivery);
        WaterReservoir(void);
        std::string get_reservoir(void);
        std::string get_municipality(void);
        int get_reservoi_id(void);
        int get_max_delivery(void);

};


#endif //DAPROJ1_WATERRESERVOIR_H
