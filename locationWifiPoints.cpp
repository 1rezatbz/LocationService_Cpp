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
    else {
        for (int i = 0; i < (int) pIfList->dwNumberOfItems; i++){
            //Get Network bss List
            pIfInfo = (WLAN_INTERFACE_INFO *) &pIfList->InterfaceInfo[i];
            dwBResult = WlanGetNetworkBssList(hClient,
                                              &pIfInfo->InterfaceGuid,
                                              NULL,
                                              dot11_BSS_type_any,
                                              0,
                                              0,
                                              &pBssList);
            if (dwBResult != ERROR_SUCCESS){
                cerr << "ERROR: WlanGetBssList faild with error: " << dwResult<<endl;
                dwRetVal =1;
            } else{
                cout << endl<< "Found" << pBssList -> dwNumberOfItems << "access points"<< endl;
                for (int k=0; k< pBssList->dwNumberOfItems;k++){
                    pBssEntry = (WLAN_BSS_ENTRY *)& pBssList->wlanBssEntries[k];
                    sprintf(accessPoint.macAddress,
                            "%02X:%02X:%02X:%02X:%02X:%02X",
                            pBssEntry -> dot11Bssid[0],
                            pBssEntry -> dot11Bssid[1],
                            pBssEntry -> dot11Bssid[2],
                            pBssEntry -> dot11Bssid[3],
                            pBssEntry -> dot11Bssid[4],
                            pBssEntry -> dot11Bssid[5]);
                    accessPoint.signalStrength = pBssEntry->lRssi;
                    wifiAPlist_.push_back(accessPoint);
                }
            }
        }
}
    return dwRetVal;

}
char* locationWifiPoints::buildRequestJSON() {
    cJSON * wifiAccessPoints = NULL;
    char *outputJSON = NULL;
    // create JSON object for considerIp
    cJSON *locationRequest = cJSON_CreateObject();
    if (cJSON_AddStringToObject(locationRequest,"considerIP", "true")==NULL){
        goto end;
    }
    // create JSON object for wifiAccessPoints
    wifiAccessPoints = cJSON_AddArrayToObject(locationRequest,"wifiAccessPoints");
    if (wifiAccessPoints == NULL){
        goto end;
    }
    // build JSON Request for each wifi point
    for (list<wifiAP>::iterator i = wifiAPlist_.begin(); i != wifiAPlist_.end();++i){
        cJSON *accessPoint = cJSON_CreateObject();
        if (cJSON_AddStringToObject(accessPoint,"macAddress", i->macAddress)==NULL){
            goto end;
        }
        if(cJSON_AddNumberToObject(accessPoint,"signalStrength",i->signalStrength)==NULL){
            goto end;
        }
        cJSON_AddItemToArray(wifiAccessPoints, accessPoint);
        outputJSON = cJSON_Print(locationRequest);
        if (outputJSON == NULL){
            cerr << "ERROR: Failed to print JSON For the wifi accsess points"<<endl;
        }
    }

    end:cJSON_Delete(locationRequest);
    return outputJSON;
}