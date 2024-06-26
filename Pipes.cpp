//
// Created by Administrador on 20/03/2024.
//

/**
*@file Pipes.cpp
*@brief Implementation of the Pipe class methods
*/

#include "Pipes.h"

Pipe::Pipe() {
    this->code_point_A = "";
    this->code_point_B = "";
    this->capacity = -1;
    this->direction = -1;
    this->id = -1;
    this->city_link = false;
}

Pipe::Pipe(std::string code_point_A, std::string code_point_B, int capacity, int direction, int id)
{
    this->code_point_A = code_point_A;
    this->code_point_B = code_point_B;
    this->capacity = capacity;
    this->direction = direction;
    this->id = id;
    this->city_link = false;
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

int Pipe::get_id(void)
{
    return this->id;
}

void Pipe::set_capacity(int capacity)
{
    this->capacity = capacity;
}

void Pipe::set_inverse_direction(void)
{
    this->direction = 2;
}

void Pipe::set_city_link(bool city_link)
{
    this->city_link = city_link;
}

void Pipe::set_code_A(std::string codeA) {
    this->code_point_A = codeA;
}

void Pipe::set_code_B(std::string codeB) {
    this->code_point_B = codeB;
}