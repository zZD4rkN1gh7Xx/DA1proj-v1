//
// Created by Administrador on 20/03/2024.
//

/**
*@file Pipes.h
*@brief Header file for the Pipe class
*/

#ifndef DAPROJ1_PIPES_H
#define DAPROJ1_PIPES_H

#include <string>

class Pipe {

    private:

        std::string code_point_A;
        std::string code_point_B;
        int capacity;
        int direction;
        int id;
        bool city_link;

    public:

        Pipe(std::string code_point_A, std::string code_point_B, int capacity, int direction, int id);
        Pipe(void);
        std::string get_code_A(void);
        std::string get_code_B(void);
        int get_capacity(void);
        int get_direction(void);
        int get_id(void);
        void set_capacity(int capacity);
        void set_inverse_direction(void);
        void set_city_link(bool city_link);
        void set_code_A(std::string codeA);
        void set_code_B(std::string codeB);


};


#endif //DAPROJ1_PIPES_H
