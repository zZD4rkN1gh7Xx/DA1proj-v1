//
// Created by Administrador on 20/03/2024.
//

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

};


#endif //DAPROJ1_PIPES_H
