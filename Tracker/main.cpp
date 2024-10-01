#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h> // Used for HTTP requests
#include <fstream> // File IO
#include "../nlohmann/json.hpp" // Read .json files
#include <filesystem> // Just to check for TOKEN.env
#include <ctime> // Gets today's time
#include <sstream> // For concatenating times
#include <chrono>

using std::cout; using std::cin; using std::endl; using std::string;

static size_t WriteCallback(void*,size_t,size_t,string*);


// Gets a json file
void getJson(string filename, string url, string token, string& readBuffer); 
string getTokenPath(); // Gets the correct token path
string getToken(); // Gets the token
string getUtcToday(); // Gets the current date in UTC
bool checkRepoCommit(nlohmann::json jsonData, string today);
bool checkAllCommit(string today, string token);
std::vector<string> getRepos(string filename, string &readBuffer, string token);

int main() {
    string today = getUtcToday();
    string token = getToken();

    /*
    string readBuffer;
    string commits_url = "https://api.github.com/repos/AndrewRoddy/Daily-Commit-Tracker/commits"; // Creates proper repo url
    getJson("Daily-Commit-Tracker", commits_url, token, readBuffer);
    nlohmann::json jsonData = nlohmann::json::parse(readBuffer);
    cout << endl << "Getting commits from " << "Daily-Commit-Tracker" << '.';
    string long_date, date;
    for (const auto& event : jsonData) {
        //try{
        
        long_date = (event["commit"]["committer"]["date"]);
        ///////
        //const std::chrono::zoned_time cur_time{ std::chrono::current_zone(), std::chrono::system_clock::now() };
            std::cout << cur_time << '\n';

        ///////
        cout << long_date << endl;
            //date = long_date.substr(0, 10);
            //cout << long_date << " | " << endl;
        //} catch (...){cout << " ";}
        //if (date == today){cout << "true";}
    }
    //cout << "false";
    */
    ///*
    cout << today;
    bool commit = checkAllCommit(today, token);
    if (commit){
        cout << endl << "You commited today!";
    } else {
        cout << endl << "You did not commit today :(";
    }
    //*/
    
}

// Checks all repositories for commit
bool checkAllCommit(string today, string token){
    string commits_url, readBuffer;
    std::vector<string> repos = getRepos("repos", readBuffer, token);
    for(int i = 0; i < repos.size(); i++){
        readBuffer = ""; readBuffer.clear(); // Completely clears readBuffer
        commits_url = "https://api.github.com/repos/AndrewRoddy/" + repos[i] + "/commits"; // Creates proper repo url
        getJson(repos[i], commits_url, token, readBuffer);
        nlohmann::json jsonData = nlohmann::json::parse(readBuffer);
        cout << endl << "Getting commits from " << repos[i] << '.';
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
        cout << '.';
    }
    return repos;
}

// Checks repository for commit
bool checkRepoCommit(nlohmann::json jsonData, string today){
    string long_date, date;
    for (const auto& event : jsonData) {
        try{
            long_date = (event["commit"]["committer"]["date"]);
            date = long_date.substr(0, 10);
            cout << long_date << " | " << endl;
        } catch (...){cout << " ";}
        if (date == today){return true;}
    }
    return false;
}

// Gets the current date in UTC time
string getUtcToday(){
    std::time_t now = std::time(nullptr);
    std::tm* utcTime = std::gmtime(&now);
    std::ostringstream oss;
    oss << std::put_time(utcTime, "%Y-%m-%d");
    string today = oss.str();
    return today;
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
        headers = curl_slist_append(headers, "Time-Zone: US/Michigan");

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

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