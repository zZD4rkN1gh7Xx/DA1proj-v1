//
// Created by Administrador on 22/03/2024.
//

#include "FileReader.h"


void FileReader::add_stations(const std::string &filename, WMSGraph &OurGraph)
{
    std::ifstream inputfile(filename);

    if(inputfile.is_open())
    {
        std::string line;
        std::getline(inputfile,line);

        while(std::getline(inputfile,line))
        {
            if (line.empty() || line.find_first_not_of(',') == std::string::npos) {
                continue;
            }

            while (!line.empty() && line.back() == ',') {
                line.pop_back();
            }

            std::istringstream iss(line);
            std::string Id, Code;

            if(std::getline(iss, Id, ',') &&
               std::getline(iss, Code, ','))
            {
                PumpingStation new_pumping_station = PumpingStation(std::stoi(Id),Code);
                OurGraph.add_pumping_station(new_pumping_station);
            }
        }
    }

    else
    {
        std::cout << "No file to open or wrong path selected!" << std::endl;
    }

    inputfile.close();
}

void FileReader::add_reservoirs(const std::string &filename ,WMSGraph &OurGraph) {

    std::ifstream inputfile(filename);

    if(inputfile.is_open())
    {

        string line, reservoir, municipality, id, code, max;
        std::getline(inputfile, line);

        while (std::getline(inputfile, reservoir, ','), std::getline(inputfile, municipality, ','), std::getline(inputfile, id, ','), std::getline(inputfile, code, ','), std::getline(inputfile, max))
        {
            WaterReservoir new_water_reservoir = WaterReservoir(reservoir, municipality, std::stoi(id), code, std::stoi(max));
            OurGraph.add_water_reservoir(new_water_reservoir);
        }
        inputfile.close();
    }
    else {
        cout << "No file to open or wrong path selected!" << std::endl;
    }

    inputfile.close();
}

void FileReader::add_cities(const std::string &filename,WMSGraph &OurGraph)
{
    std::ifstream in(filename);

    if(in.is_open()) {
        string line, city, id, code, demand, population;
        std::getline(in, line);

        while (std::getline(in, city, ','), std::getline(in, id, ','), std::getline(in, code, ','), std::getline(in, demand, ','), std::getline(in, population))
        {

            std::string result;
            for (char c : population) {

                if (c != '\"' && c != ',') {
                    result += c;
                }
            }
            DeliverySite new_delivery_site = DeliverySite(city, std::stoi(id), code, std::stod(demand), std::stoi(result));
            OurGraph.add_delivery_site(new_delivery_site);
        }
        in.close();
    }
    else
        cout << "No file to open or wrong path selected!" << std::endl;
}


void FileReader::add_pipes(const std::string &filename, WMSGraph &OurGraph)
{
    std::ifstream in(filename);

    if (in.is_open())
    {
        std::string line;
        std::getline(in, line);

        while (std::getline(in, line))
        {
            std::istringstream iss(line);
            std::string service_point_A, service_point_B, capacity, direction;

            if (std::getline(iss, service_point_A, ',') &&
                std::getline(iss, service_point_B, ',') &&
                std::getline(iss, capacity, ',') &&
                std::getline(iss, direction))
            {
                Pipe new_pipe(service_point_A, service_point_B, std::stoi(capacity), std::stoi(direction));
                OurGraph.add_pipe(new_pipe);
            }
        }
    }
    else
    {
        std::cout << "No file to open or wrong path selected!" << std::endl;
    }

    in.close();
}