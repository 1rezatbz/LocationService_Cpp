//
// Created by sgrfazli on 09/03/2023.
//

#ifndef LOCATIONSERVICE_CPP_LOCATIONREQUES_H
#define LOCATIONSERVICE_CPP_LOCATIONREQUES_H
#include <iostream>
#include <cstring>
#include <string>
#include "cJSON.h" // JSON support https://github.com/DaveGamble/cJSON
//#include "curl.h" // curl support https://curl.haxx.se/

#define GEO_API_BASE_URL  "https://www.googleapis.com/geolocation/v1/geolocate?key="#
#define GEO_API_KEY "AIzaSyBbzftXRb-82QIOH0T3_FUMif402VdVo-c"
#define GEO_API_REQUEST_URL GEO_API_BASE_URL GEO_API_KEY

class locationRequest {
    void getLocation(char *jsonPayload);
    void printLocationInfo(char *response);
private:
    struct MemoryStruct{
        char * memory;
        size_t size;
    };
    static size_t writeMemoryCallback(void *contents,
                                      size_t size,
                                      size_t nmemb,
                                      void *userp);
};


#endif //LOCATIONSERVICE_CPP_LOCATIONREQUES_H
