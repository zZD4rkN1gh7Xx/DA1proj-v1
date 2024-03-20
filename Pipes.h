//
// Created by Administrador on 20/03/2024.
//

#ifndef DAPROJ1_PIPES_H
#define DAPROJ1_PIPES_H

#include <string>

class Pipe {

    private:

        std::string service_point_A;
        std::string service_point_B;
        int capacity;
        int direction;

    public:

        Pipe(std::string service_point_A, std::string service_point_B, int capacity, int direction);
        Pipe(void);
        std::string get_point_A(void);
        std::string get_point_B(void);
        int get_capacity(void);
        int get_direction(void);

};


#endif //DAPROJ1_PIPES_H
