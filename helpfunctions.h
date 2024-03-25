//
// Created by Administrador on 25/03/2024.
//

#include <string>

std::string capitalizeFirstLetter(std::string str) {
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

std::vector<WaterReservoir> get_all_sources(std::string sink)
{

}