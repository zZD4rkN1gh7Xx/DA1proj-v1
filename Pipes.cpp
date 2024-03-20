//
// Created by Administrador on 20/03/2024.
//

#include "Pipes.h"


Pipe::Pipe(std::string service_point_A, std::string service_point_B, int capacity, int direction)
{
    this->service_point_A = service_point_A;
    this->service_point_B = service_point_B;
    this->capacity = capacity;
    this->direction = direction;
}

std::string Pipe::get_point_A(void)
{
    return this->service_point_A;
}

std::string Pipe::get_point_B(void)
{
    return this->service_point_B;
}

int Pipe::get_capacity(void)
{
    return this->capacity;
}

int Pipe::get_direction(void)
{
    return this->direction;
}