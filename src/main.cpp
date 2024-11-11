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

#include "..\\include\\tzone.hpp"
#include "..\\include\\tracker.hpp"
#include "..\\include\\tray.hpp"
#include "..\\include\\tokens.hpp"

using std::cout; using std::cin; using std::endl; using std::string;

int main() {

    token_check();
    
    string today; bool commit;
    string token = getToken();

    WNDCLASS wc = trayStart();
    HWND hwnd = createWindow();
    HICON hIcon = createIcon("..\\assets\\icons\\32x\\Loading.ico");
    NOTIFYICONDATA nid = createData(hwnd, hIcon);

    int second_loop = 60; // The amount of seconds between .json checks

    MSG msg; // Message Loop
    while (true){
        // Checks for if the user presses the icon.
        if(GetMessage(&msg, NULL, 0, 0)){
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            exit(0);
        }

        // Checks for new commits every 60 seconds.
        second_loop += 1;
        if (second_loop >= 60){
            today = getToday(); cout << today;
            commit = checkAllCommit(today, token);
            removeIcon(nid, hIcon);
            if (commit){ cout << " Yes" << endl;
                hIcon = createIcon("..\\assets\\icons\\32x\\Green.ico");
            } else { cout << " No" << endl;
                hIcon = createIcon("..\\assets\\icons\\32x\\Empty.ico");
            }

            nid = createData(hwnd, hIcon);
            second_loop = 0;
        }
    
        

        // Sleep for 1 minute // Apparently this is less prone to errors?
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
        
        
    }
    
    return 0;
}

