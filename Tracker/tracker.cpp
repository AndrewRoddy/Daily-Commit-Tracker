#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h> // Used for HTTP requests
#include <fstream> // File IO
#include "../lib/nlohmann/json.hpp" // Read .json files
#include <filesystem> // Just to check for TOKEN.env
#include <ctime> // Gets today's time
#include <sstream> // For concatenating times
#include <unordered_map>

#include "tzone.hpp"
#include "tracker.hpp"

using std::cout; using std::cin; using std::endl; using std::string;

// Checks all repositories for commit
bool checkAllCommit(string today, string token){
    string commits_url, readBuffer;
    std::vector<string> repos = getRepos("repos", readBuffer, token);
    for(int i = 0; i < repos.size(); i++){
        readBuffer = ""; readBuffer.clear(); // Completely clears readBuffer
        commits_url = "https://api.github.com/repos/AndrewRoddy/" + repos[i] + "/commits"; // Creates proper repo url
        getJson(repos[i], commits_url, token, readBuffer);
        nlohmann::json jsonData = nlohmann::json::parse(readBuffer);
        //cout << endl << "Getting commits from " << repos[i] << '.';
        if (checkRepoCommit(jsonData, today)) {
            return true;
        }
    }
    return false;
}

// Returns string vector of all repository names
std::vector<string> getRepos(string filename, string &readBuffer, string token){
    getJson(filename,"https://api.github.com/user/repos?type=all&page=&per_page=1000",token,readBuffer);
    nlohmann::json jsonData = nlohmann::json::parse(readBuffer);
    std::vector<string> repos;
    string repository;
    for (const auto& event : jsonData) {
        repository = event["name"]; // Gets repository name
        repos.push_back(repository); // Adds repository to list
        //cout << '.';
    }
    return repos;
}

// Checks repository for commit
bool checkRepoCommit(nlohmann::json jsonData, string today){
    string long_date, convert_date, date;
    for (const auto& event : jsonData) {
        try{
            long_date = (event["commit"]["committer"]["date"]);
            convert_date = convertTZ(long_date, getTZ("EDT"));
            date = convert_date.substr(0, 10);
            //cout << endl << date << " | " << endl;
        } catch (...){break;}
        if (date == today){
            return true;
        } else {return false;}
    }
    return false;
}

// Gets the current date in UTC time
string getToday(){
    std::time_t now = std::time(nullptr); // Get current time
    std::tm* localTime = std::localtime(&now); // Convert to local
    std::ostringstream oss;
    oss << std::put_time(localTime, "%Y-%m-%d"); // Formatting
    return oss.str();
}

// Gets the proper token path based on who is using it
string getTokenPath(){
    if (std::filesystem::exists("..\\TOKENS.env")) { // Where my tokens / developer tokens are stored
        return "..\\TOKENS.env";
    } else {
        return "..\\TOKEN.env";
    }
}

// Gets the token
string getToken(){
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
    return token;
}

// Gets a Json file from a url
// Some curl code taken from the internet. 
// I added the parameters and modified functionality
void getJson(string filename, string url, string token, string& readBuffer){ 
    CURL* curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) { // Initialize CURL
        // Set the URL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Sets authorization
        std::string authHeader = "Authorization: token " + token;
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, authHeader.c_str());

        // Sets the proper user agent
        headers = curl_slist_append(headers, "User-Agent: AndrewRoddy");

        // Generates the times in the proper time zone
        //headers = curl_slist_append(headers, "Time-Zone: US/Michigan");

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Set the CA certificates path (adjust this path as needed)
        curl_easy_setopt(curl, CURLOPT_CAINFO, "C:\\.Coding\\Daily-Commit-Tracker\\cacert.pem");

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            // Save the received JSON data to a file
            string total_name = "json/" + filename + ".json";
            std::ofstream outFile(total_name);
            if (outFile.is_open()) {
                outFile << readBuffer;
                outFile.close();
                //std::cout << "JSON data saved to json/" << name << ".json" << std::endl;
            } else {
                std::cerr << "Failed to open events.json for writing" << std::endl;
            }
        }

        // Cleanup
        curl_easy_cleanup(curl);
    }
}

// Code completely taken from the internet
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userData) {
    size_t totalSize = size * nmemb;
    userData->append((char*)contents, totalSize);
    return totalSize;
}
