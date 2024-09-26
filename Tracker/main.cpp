#include <iostream>
//#include "..\curl\curl-8.10.1_1-win64-mingw\curl-8.10.1_1-win64-mingw\include\curl\curl.h"
#include <curl/curl.h>

int main() {
    std::cout << "Starting CURL test..." << std::endl;

    CURL* curl = curl_easy_init();
    if (curl) {
        std::cout << "CURL initialized successfully." << std::endl;
        curl_easy_cleanup(curl);
    } else {
        std::cout << "Failed to initialize CURL" << std::endl;
    }

    system("PAUSE");

    return 0;
}
