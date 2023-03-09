//
// Created by sgrfazli on 09/03/2023.
//

#include "locationWifiPoints.h"
using namespace std;

int locationWifiPoints::getWifiNetworks() {
    //initialise variables
    // HANDLE data type in the WIN os that is used to represent a handle to a resource or an object in the system
    HANDLE hClient = NULL;
    //DWORD 32-bit unsigned integer,
    DWORD dwMaxClient = 2;
    DWORD dwCurVersion = 0;
    DWORD dwResult = 0;
    DWORD dwBResult = 0;
    DWORD dwRetVal = 0;
    wifiAP accessPoint{"00:00:00:00:00:00",0};
    // variables used for WlanEnumInterfaces
    PWLAN_INTERFACE_INFO_LIST pIfList = NULL;
    PWLAN_INTERFACE_INFO pIfInfo= NULL;
    PWLAN_BSS_LIST pBssList = NULL;
    PWLAN_BSS_ENTRY pBssEntry = NULL;

    /*WlanOpenHandle is a function in the Windows Native Wifi API
     * that is used to open a handle to the WLAN service on a computer.
     * The function creates a client session to the WLAN service, which
     * allows the application to access and manipulate the WLAN interfaces
     * and network profiles on the system.*/
    dwBResult = WlanOpenHandle(dwMaxClient,NULL,&dwCurVersion,&hClient);
    if(dwResult != ERROR_SUCCESS){
        cerr << "ERROR: WlanOpenHandle failed with error: " << dwResult<<endl;
        return 1;}
    /* WlanEnumInterfaces is a function in the Windows Native Wifi API
     that is used to enumerate the wireless LAN (WLAN) interfaces available
    on a computer. */
    dwResult = WlanEnumInterfaces(hClient, NULL, &pIfList);
    if(dwResult != ERROR_SUCCESS){
        cerr << "ERROR: WlanEnumInterfaces failed with error: " << dwResult<<endl;
        return 1;}
    else{  
}




}
char* locationWifiPoints::buildRequestJSON() {
}