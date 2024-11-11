#include <iostream>
#include <string>
#include <fstream>
#include <filesystem> // Just to check for TOKENS.env
#include <cstdlib>
#include "..\\include\\tokens.hpp"

using std::cin; using std::cout; using std::endl;

void token_check() {

    // Construct the command to download the file using wget
    if (std::filesystem::exists("..\\cacert.pem") == false){
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