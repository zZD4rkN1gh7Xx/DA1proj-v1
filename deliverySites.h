//
// Created by Administrador on 20/03/2024.
//

#ifndef DAPROJ1_DELIVERYSITES_H
#define DAPROJ1_DELIVERYSITES_H

#include <string>

class DeliverySite {

    private:

        std::string city;
        int delivery_site_id;
        std::string delivery_site_code;
        int demand;
        int population;

    public:

        DeliverySite(std::string city, int delivery_site_id, std::string delivery_site_code, int demand, int population);
        DeliverySite(void);
        std::string get_city(void);
        int get_delivery_site_id(void);
        std::string get_delivery_site_code(void);
        int get_demand(void);
        int get_population(void);

};


#endif //DAPROJ1_DELIVERYSITES_H
