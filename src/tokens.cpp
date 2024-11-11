#include <iostream>
#include <string>
#include <fstream>
#include <filesystem> // Just to check for TOKENS.env
#include <cstdlib>
#include "..\\include\\tokens.hpp"

using std::cin; using std::cout; using std::endl;

void token_check() {

    if (std::filesystem::exists("..\\cacert.pem") == false){
        // Construct the command to download the file using curl
        system("curl -s -o ..\\cacert.pem https://curl.se/ca/cacert.pem");
    }
    
    // Gets the proper token path based on who is using it
    if (std::filesystem::exists("..\\TOKENS.env") == false) { // Where my tokens / developer tokens are stored
        std::string token;
        cout << "Input your github token: ";
        cin >> token;

        std::ofstream file("..\\TOKENS.env"); // Create an ofstream object to handle output to the file
        file << "GITHUB_TOKEN=";
        file << token;

        file.close();
    }
}

// Gets the token
std::string getToken(){
    std::ifstream file("..\\TOKENS.env");
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
