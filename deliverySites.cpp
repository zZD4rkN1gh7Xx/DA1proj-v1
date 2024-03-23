//
// Created by Administrador on 20/03/2024.
//

#include "deliverySites.h"

DeliverySite::DeliverySite(std::string city, int delivery_site_id, std::string delivery_site_code, int demand, int population) : Agua(delivery_site_id, delivery_site_code)
{
    this->city = city;
    this->demand = demand;
    this->population = population;

}

std::string DeliverySite::get_city(void)
{
    return this->city;
}

int DeliverySite::get_demand(void)
{
    return this->demand;
}

int DeliverySite::get_population(void)
{
    return this->population;
}

std::string DeliverySite::get_delivery_site_code(void)
{
    return this->delivery_site_code;
}
