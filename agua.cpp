//
// Created by Administrador on 22/03/2024.
//

#include "agua.h"


Agua::Agua(int id, std::string code)
{
    this->id = id;
    this->code = code;
}


int Agua::get_id(void)
{
    return this->id;
}

std::string Agua::get_code(void)
{
    return this->code;
}