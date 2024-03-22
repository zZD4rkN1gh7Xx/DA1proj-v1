//
// Created by Administrador on 22/03/2024.
//

#ifndef DAPROJ1_AGUA_H
#define DAPROJ1_AGUA_H

#include <string>

class Agua {

    private:

        int id;
        std::string code;

    public:

        Agua(int id, std::string code);
        Agua(void);
        int get_id(void);
        std::string get_code(void);

};


#endif //DAPROJ1_AGUA_H
