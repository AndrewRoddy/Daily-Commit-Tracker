#include <iostream>
#include <vector>
#include <string>
#include <chrono> // For sleep timer
#include <thread> // Used in sleep timer
//#include <sstream> // For concatenating times

//#include <ctime> // Gets today's time

//#include <string>
//#include <vector>
//#include <curl/curl.h> // Used for HTTP requests
//#include <fstream> // File IO
//#include "..\\lib\\nlohmann\\json.hpp" // Read .json files
//#include <filesystem> // Checks for where code is being run // Just to check for TOKEN.env

//#include <unordered_map>

/*


//#include "..\\include\\pather.hpp"
*/

#include "..\\include\\tracker.hpp"
#include "..\\include\\tokens.hpp"
#include "..\\include\\tray.hpp"
#include "..\\include\\tzone.hpp"

int main() {
    std::cout << "Start:" << std::endl;
    
    token_check(); // Checks and creates tokens
    
    std::string token = getToken(); // Gets the current token

    
    // Tray Icon Functions
    std::cout << "Loading Tray." << std::endl;
    WNDCLASS wc = trayStart();
    HWND hwnd = createWindow();
    HICON hIcon = createIcon("..\\assets\\icons\\32x\\Loading.ico");
    NOTIFYICONDATA nid = createData(hwnd, hIcon);
    
    
    // *Start at high number to check for commits before waiting
    int second_loop = 60; // Second loop index 
    int check_interval = 30; // The amount of seconds between .json checks
    std::string today;
    bool commit;
    MSG msg; // Message Loop
    
    std::cout << "Starting Loop." << std::endl;

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
            std::cout << today; // Prints the current day
            
            
            try {
                commit = checkAllCommit(today, token); // True if commit today
            } catch(...) { // I know this is bad but I need to use it
                std::this_thread::sleep_for(std::chrono::seconds(5)); // Wait 5 seconds before trying again
                continue;
            }
            
            removeIcon(nid, hIcon); // Clears old icon to show new
            if (commit){ std::cout << " Yes" << std::endl; // Yes Commit -> Green Box
                hIcon = createIcon("..\\assets\\icons\\32x\\Green.ico");
            } else { std::cout << " No" << std::endl; // No Commit -> Empty Box
                hIcon = createIcon("..\\assets\\icons\\32x\\Empty.ico");
            }
            nid = createData(hwnd, hIcon); // Loads the next icon
            second_loop = 0; // Resets second loop
            
        }

        // Sleep for 1 second
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
        
        
    }
    
    return 0;
    
    int a; std::cin >> a;
    return 0;
}

