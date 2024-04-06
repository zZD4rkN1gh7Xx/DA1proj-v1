//
// Created by Administrador on 22/03/2024.
//

/**
*@file agua.cpp
*@brief Implementation of the agua class methods
*/

#include "agua.h"


Agua::Agua(int id, std::string code)
{
    this->id = id;
    this->code = code;
}

Agua::Agua(void)
{
    this->id = 0;
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
    if (this->code[0] == other.code[0]) {

        if (this->id == other.id) {
            return true;
        }
        else {
            return false;
        }
    }

    else {
        return false;
    }
}

bool Agua::operator!=(Agua& other)
{

    if (this->code[0] == other.get_code()[0]) {

        if (this->id == other.get_id()) {
            return false;
        }
        else {
            return true;
        }
    }

    else {
        return true;
    }
}