#include <iostream>
/*
#include <string>
#include <vector>
#include <curl/curl.h> // Used for HTTP requests
#include <fstream> // File IO
#include "..\\lib\\nlohmann\\json.hpp" // Read .json files
#include <filesystem> // Checks for where code is being run // Just to check for TOKEN.env
#include <ctime> // Gets today's time
#include <sstream> // For concatenating times
#include <unordered_map>
#include <chrono>
#include <thread>


#include "..\\include\\tzone.hpp"
#include "..\\include\\tracker.hpp"
#include "..\\include\\tray.hpp"
#include "..\\include\\tokens.hpp"
*/
using std::cout; using std::cin; using std::endl; //using std::string;

//std::string adjust_path(const std::string& relative_path); // Needs to be here because needs to help link other files

int main() {
    std::cout << "HI" << std::endl;
    /*
    // Example usage
    std::string relative_file = "assets\\data.txt";
    std::string full_path = adjust_path(relative_file);

    std::cout << "Adjusted Path: " << full_path << std::endl;

    // You can now use `full_path` to open files, etc.
    std::filesystem::path current_path = std::filesystem::current_path();
    cout << current_path << endl;
    */
    /*
    token_check(); // Checks and creates tokens
    string token = getToken(); // Gets the current token

    // Tray Icon Functions
    WNDCLASS wc = trayStart();
    HWND hwnd = createWindow();
    HICON hIcon = createIcon("assets\\icons\\32x\\Loading.ico");
    NOTIFYICONDATA nid = createData(hwnd, hIcon);

    // *Start at high number to check for commits before waiting
    int second_loop = 60; // Second loop index 
    int check_interval = 30; // The amount of seconds between .json checks
    string today; bool commit; MSG msg; // Message Loop

    while (true){
        // Checks for if the user presses the icon.
         
        //GetMessage() pauses the program if queue is empty
        //PeekMessage() gets and handles user input
        //PM_REMOVE removes the message from queue after peeking
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){ 
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Checks for new commits every 30 seconds.
        second_loop += 1;
        if (second_loop >= 30){ // Checks
            today = getToday(); // Gets current day
            cout << today; // Prints current date to console
            try {
                commit = checkAllCommit(today, token); // True if commit today
            } catch(...) { // I know this is bad but I need to use it
                std::this_thread::sleep_for(std::chrono::seconds(5)); // Wait 5 seconds before trying again
                continue;
            }
            removeIcon(nid, hIcon); // Clears old icon to show new
            if (commit){ cout << " Yes" << endl; // Yes Commit -> Green Box
                hIcon = createIcon("assets\\icons\\32x\\Green.ico");
            } else { cout << " No" << endl; // No Commit -> Empty Box
                hIcon = createIcon("assets\\icons\\32x\\Empty.ico");
            }
            nid = createData(hwnd, hIcon); // Loads the next icon
            second_loop = 0; // Resets second loop
        }

        // Sleep for 1 second
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
        
        
    }
    
    return 0;
    */
}
/*
std::string adjust_path(const std::string& relative_path) {
    std::filesystem::path current_path = std::filesystem::current_path(); // The current path of where it's being run
    std::string current_path_str = current_path.string(); // convert the current path to a string

    // src time
    size_t src_pos = current_path_str.find("src"); // Checks for src
    if (src_pos != std::string::npos) { // If it is in src folder
        current_path_str = current_path_str.substr(0, src_pos); // Remove the src part from the path
    }

    // Bin time
    size_t bin_pos = current_path_str.find("bin"); // Checks for bin
    if (bin_pos != std::string::npos) { // If it is in bin folder
        current_path_str = current_path_str.substr(0, bin_pos); // Remove the bin part from the path
    }
    return (std::filesystem::path(current_path_str) / relative_path).string(); // Return in the fixed path
}

*/