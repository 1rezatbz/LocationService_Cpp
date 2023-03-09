//
// Created by sgrfazli on 09/03/2023.
//

#ifndef LOCATIONSERVICE_CPP_LOCATIONWIFIPOINTS_H
#define LOCATIONSERVICE_CPP_LOCATIONWIFIPOINTS_H
#include <iostream>
#include <string>
# include <list>
#include <windows.h>
#include <wlanapi.h>
#include "cJSON.h" // JSON support https://github.com/DaveGamble/cJSON


class locationWifiPoints {
public:
    int getWifiNetworks();
    // char* in the method  indicates that the method returns a pointer.
    char* buildRequestJSON();
private:
    struct wifiAP{
        char macAddress[44];
        long signalStrength;
    };
    std::list<wifiAP> wifiAPlist_;
};


#endif //LOCATIONSERVICE_CPP_LOCATIONWIFIPOINTS_H
