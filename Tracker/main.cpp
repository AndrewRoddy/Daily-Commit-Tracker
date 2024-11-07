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
#include <chrono>
#include <thread>

#include "tzone.hpp"
#include "tracker.hpp"
#include "tray.hpp"

using std::cout; using std::cin; using std::endl; using std::string;

int main() {
    string today; bool commit;
    string token = getToken();

    WNDCLASS wc = trayStart();
    HWND hwnd = createWindow();
    HICON hIcon = createIcon("..\\assets\\icons\\red_square.ico");
    NOTIFYICONDATA nid = createData(hwnd, hIcon);

    MSG msg; // Message Loop
    while (true){
        today = getToday();
        cout << today;
        commit = checkAllCommit(today, token);

        removeIcon(nid, hIcon);
        if (commit){
            cout << " Yes" << endl;
            HICON hIcon = createIcon("..\\assets\\icons\\green_square.ico");
            NOTIFYICONDATA nid = createData(hwnd, hIcon);
        } else {
            cout << " No" << endl;
            HICON hIcon = createIcon("..\\assets\\icons\\red_square.ico");
            NOTIFYICONDATA nid = createData(hwnd, hIcon);
        }

        // Checks for if the user presses the icon.
        if(GetMessage(&msg, NULL, 0, 0)){
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            exit(0);
        }

        // Sleep for 1 minute
        std::this_thread::sleep_for(std::chrono::minutes(1)); // Apparently this is less prone to errors?
    }

    

    return 0;
    /*
    string today; bool commit;
    string token = getToken();
    while(true){
        today = getToday();
        cout << today;
        commit = checkAllCommit(today, token);
        if (commit){
            cout << " Yes" << endl;
        } else {
            cout << " No" << endl;
        }
        
        // Apparently this is less prone to errors?
        std::this_thread::sleep_for(std::chrono::minutes(1));
    }
    */
    
}

