cmake_minimum_required(VERSION 3.26)
project(DA1proj_v1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DA1proj_v1
        agua.cpp
        deliverySites.cpp
        FileReader.cpp
        main.cpp
        Pipes.cpp
        pumpingStations.cpp
        waterReservoir.cpp
        WMSGraph.cpp
        Menu.cpp
)
