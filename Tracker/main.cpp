#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h> // Used for HTTP requests
#include <fstream> // File IO
#include "../nlohmann/json.hpp" // Read .json files
#include <filesystem> // Just to check for TOKEN.env
#include <ctime> // Gets today's time
#include <sstream> // For concatenating times
#include <unordered_map>
#include <chrono>
#include <thread>

#include "tzone.hpp"
#include "tracker.hpp"

using std::cout; using std::cin; using std::endl; using std::string;


int main() {
    string today;
    string token = getToken();

    while(true){
        today = getToday();
        cout << today;
        bool commit = checkAllCommit(today, token);
        if (commit){
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
        
        // Apparently this is less prone to errors?
        std::this_thread::sleep_for(std::chrono::minutes(1));
    }
    
}
