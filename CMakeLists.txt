cmake_minimum_required(VERSION 3.23.2)
project(LocationService_Cpp)

set(CMAKE_CXX_STANDARD 17)



add_executable(LocationService_Cpp
        main.cpp
        locationWifiPoints.h
        locationWifiPoints.cpp
#        locationRequest.h
#        locationRequest.cpp
        cJSON.c
        )
target_link_libraries(LocationService_Cpp curl wlanapi)
