#include <iostream>
#include <string>
#include "C:\\.Coding\\Daily-Commit-Tracker\\curl-8.10.1_1-win64-mingw\\include\\curl\\curl.h"
#include <fstream>

// Callback function to handle the incoming data
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userData) {
    size_t totalSize = size * nmemb;
    userData->append((char*)contents, totalSize);
    return totalSize;
}

int main() {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    // Initialize CURL
    curl = curl_easy_init();
    if (curl) {
        // Set the URL
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.github.com/users/AndrewRoddy/events");

        // Specify the callback function to write the data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Set the user agent
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");

        // Set the CA certificates path (adjust this path as needed)
        curl_easy_setopt(curl, CURLOPT_CAINFO, "C:\\curl\\cacert.pem");

        // Perform the request
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
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

    return 0;
}
