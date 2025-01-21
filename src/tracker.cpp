
#include "..\\include\\tzone.hpp"
#include "..\\include\\tracker.hpp"
#include "..\\include\\tokens.hpp"

// Checks all repositories for commit
bool checkAllCommit(std::string today, std::string token){
    std::string commits_url, readBuffer;
    std::vector<std::string> repos = getRepos("repos", readBuffer, token);
    
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

// Returns std::string vector of all repository names
std::vector<std::string> getRepos(std::string filename, std::string &readBuffer, std::string token){
    getJson(filename,"https://api.github.com/user/repos?type=all&page=&per_page=1000",token,readBuffer);
    nlohmann::json jsonData = nlohmann::json::parse(readBuffer);
    std::vector<std::string> repos;
    std::string repository;
    for (const auto& event : jsonData) {
        repository = event["name"]; // Gets repository name
        repos.push_back(repository); // Adds repository to list
    }
    return repos;
}


// Checks repository for commit
bool checkRepoCommit(nlohmann::json jsonData, std::string today){
    std::string long_date, convert_date, date;
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



// Gets a Json file from a url
// Some curl code taken from the internet. 
// I added the parameters and modified functionality
void getJson(std::string filename, std::string url, std::string token, std::string& readBuffer){ 
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

        // I edited this line without testing it
        curl_easy_setopt(curl, CURLOPT_CAINFO, "..\\cacert.pem");

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            // Save the received JSON data to a file
            std::string total_name = "../json/" + filename + ".json";
            std::ofstream outFile(total_name);
            if (outFile.is_open()) {
                outFile << readBuffer;
                outFile.close();
                //std::cout << "JSON data saved to json/" << filename << ".json" << std::endl;
            } else {
                std::cerr << "Failed to open " << filename << ".json for writing" << std::endl;
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
