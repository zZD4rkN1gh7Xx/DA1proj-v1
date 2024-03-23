//
// Created by Administrador on 22/03/2024.
//

#include "agua.h"


Agua::Agua(int id, std::string code)
{
    this->id = id;
    this->code = code;
}

Agua::Agua(void)
{
    this->id = NULL;
    this->code = "";
}


int Agua::get_id(void)
{
    return this->id;
}

std::string Agua::get_code(void)
{
    return this->code;
}

bool Agua::operator==(const Agua& other) const
{
    return (this->id == other.id);
}

bool Agua::operator!=(Agua& other)
{
    return !(this->id == other.id);
}