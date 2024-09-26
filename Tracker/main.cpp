#include <iostream>
#include <string>
#include <curl/curl.h>
#include <fstream>
#include "../nlohmann/json.hpp"
#include <filesystem>
#include <algorithm>

using std::cout; using std::cin; using std::endl;
using std::string;

static size_t WriteCallback(void*,size_t,size_t,string*);
void getJson(string url, string token, string& readBuffer);

int main() {
    
    std::ifstream file(getTokenPath());
    std::string token;
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            if (line.find("GITHUB_TOKEN=") != std::string::npos) {
                token = line.substr(line.find('=') + 1);
                break;
            }
        }
        file.close();
    } else {
        std::cerr << "Unable to open token file." << std::endl;
    }
    //cout << token;

    string readBuffer;

    string commits = "https://api.github.com/repos/AndrewRoddy/Daily-Commit-Tracker/commits";
    string repos = "https://api.github.com/users/AndrewRoddy/repos";

    

    getJson(repos, token, readBuffer);
    
    

    nlohmann::json jsonData = nlohmann::json::parse(readBuffer);
    // Output the JSON data
    //std::cout << std::setw(4) << jsonData << std::endl;  // Pretty print the JSON
    //for (const auto& event : jsonData) {
    //    std::cout << std::setw(4) << event["created_at"] << std::endl;

        //For the commits link
    //    std::cout << std::setw(4) << event["commit"]["author"]["date"] << std::endl;
    //}

    return 0;
}

// Gets the proper token path based on who is using it
string getTokenPath(){
    if (std::filesystem::exists("..\\TOKENS.env")) { // Where my tokens / developer tokens are stored
        return "..\\TOKENS.env";
    } else {
        return "..\\TOKEN.env";
    }
}

// Gets a Json
// Code taken from the internet.
// Curl is a nightmare!
// I added the parameter though :)
void getJson(string url, string token, string& readBuffer){ 
    CURL* curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) { // Initialize CURL

        // Set the URL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        //curl_easy_setopt(curl, CURLOPT_URL, "https://api.github.com/user/repos");

        // Specify the callback function to write the data
        //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        //curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Sets authorization
        std::string authHeader = "Authorization: token " + token;
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, authHeader.c_str());

        headers = curl_slist_append(headers, "User-Agent: AndrewRoddy");

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Set the user agent
        //curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");
        //curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/8.10.1");

        // Set the CA certificates path (adjust this path as needed)
        curl_easy_setopt(curl, CURLOPT_CAINFO, "C:\\.Coding\\Daily-Commit-Tracker\\curl-8.10.1_1-win64-mingw\\cacert.pem");

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

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