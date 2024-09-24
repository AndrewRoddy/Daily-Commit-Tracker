#include <iostream>
#include <iostream>
#include <string>

// Download Curl First
//#include "..\curl-8.10.1\curl-8.10.1\include\curl\curl.h"

// Downloaded for you :)
#include "..\nlohmann\json.hpp"

using std::cout; using std::cin; using std::endl;
/*
// I didn't write this fuction but everyone said I needed it
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main(){
    cout << "Test!";

    // Curl Setup
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "http://www.google.com");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    std::cout << readBuffer << std::endl;
    }
}


*/