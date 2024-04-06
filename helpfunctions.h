//
// Created by Administrador on 25/03/2024.
//

/**

*@file helpfunctions.h
*@brief Header file for some functions that we will use on the project
*/

#ifndef HELPFUNCTIONS_H
#define HELPFUNCTIONS_H

#include <string>
#include <vector>
#include <queue>
#include "WMSGraph.h"


inline std::string capitalizeFirstLetter(std::string str) {
    if (str.empty()) {
        return str; // Return the unchanged string if it's empty
    }

    // Capitalize the first letter
    str[0] = toupper(str[0]);

    // Convert the rest of the letters to lowercase
    for (size_t i = 1; i < str.length(); ++i) {
        str[i] = tolower(str[i]);
    }

    return str;
}




#endif // HELPFUNCTIONS_H