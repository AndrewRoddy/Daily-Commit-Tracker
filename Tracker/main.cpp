#include <iostream>
#include <string>
#include <curl/curl.h>
#include <fstream>
#include "../nlohmann/json.hpp"

using std::cout; using std::cin; using std::endl;
using std::string;

static size_t WriteCallback(void*,size_t,size_t,string*);
void getJson(string url, string& readBuffer);

int main() {
    string readBuffer;

    string events = "https://api.github.com/users/AndrewRoddy/events";
    string commits = "https://api.github.com/repos/AndrewRoddy/MyLlama/commits";
    string repos = "https://api.github.com/users/AndrewRoddy/repos";

    getJson(events, readBuffer);
    
    nlohmann::json jsonData = nlohmann::json::parse(readBuffer);
    // Output the JSON data
    //std::cout << std::setw(4) << jsonData << std::endl;  // Pretty print the JSON
    for (const auto& event : jsonData) {
        std::cout << std::setw(4) << event["created_at"] << std::endl;

        // For the commits link
        //std::cout << std::setw(4) << event["commit"]["author"]["date"] << std::endl;
    }
    return 0;
}

// Gets a Json
// Code taken from the internet.
// Curl is a nightmare!
// I added the parameter though :)
void getJson(string url, string& readBuffer){ 
    CURL* curl;
    curl = curl_easy_init();

    CURLcode res;
    
    

    if (curl) { // Initialize CURL

        // Set the URL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Specify the callback function to write the data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Set the user agent
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");

        // Set the CA certificates path (adjust this path as needed)
        curl_easy_setopt(curl, CURLOPT_CAINFO, "C:\\.Coding\\Daily-Commit-Tracker\\curl-8.10.1_1-win64-mingw\\cacert.pem");

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            // Save the received JSON data to a file
            std::ofstream outFile("events.json");
            if (outFile.is_open()) {
                outFile << readBuffer;
                outFile.close();
                std::cout << "JSON data saved to events.json" << std::endl;
            } else {
                std::cerr << "Failed to open events.json for writing" << std::endl;
            }
        }

        // Cleanup
        curl_easy_cleanup(curl);
    }
}

// Callback function to handle the incoming data
// Code completely taken from the internet
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userData) {
    size_t totalSize = size * nmemb;
    userData->append((char*)contents, totalSize);
    return totalSize;
}