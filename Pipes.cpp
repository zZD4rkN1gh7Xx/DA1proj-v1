//
// Created by Administrador on 20/03/2024.
//

#include "Pipes.h"


Pipe::Pipe(std::string code_point_A, std::string code_point_B, int capacity, int direction)
{
    this->code_point_A = code_point_A;
    this->code_point_B = code_point_B;
    this->capacity = capacity;
    this->direction = direction;
}

std::string Pipe::get_code_A(void)
{
    return this->code_point_A;
}

std::string Pipe::get_code_B(void)
{
    return this->code_point_B;
}

int Pipe::get_capacity(void)
{
    return this->capacity;
}

int Pipe::get_direction(void)
{
    return this->direction;
}