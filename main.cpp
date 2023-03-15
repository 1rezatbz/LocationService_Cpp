//
// Created by sgrfazli on 09/03/2023.
//
#include <iostream>
#include <cstring>
#include <string>

#include "locationRequest.h"
#include "locationWifiPoints.h"
using namespace std;
int main(){
    cout<<"hi"<<endl;
    locationWifiPoints wifiAccess;
    wifiAccess.getWifiNetworks();
    char * jsonPayload = wifiAccess.buildRequestJSON();
    return 0;
}