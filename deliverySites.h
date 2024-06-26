//
// Created by Administrador on 20/03/2024.
//

/**

*@file deliverySites.h
*@brief Header file for the DeliverySite class an extention of the Agua class
*/

#ifndef DAPROJ1_DELIVERYSITES_H
#define DAPROJ1_DELIVERYSITES_H

#include <string>
#include "agua.h"

class DeliverySite : public Agua {

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
        void set_demand(int demand);
        bool operator<(const DeliverySite& other) const;


};


#endif //DAPROJ1_DELIVERYSITES_H
