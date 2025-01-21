// Tracker Functions
// Andrew Roddy
// 9/26/24

#pragma once
#ifndef tracker
#define tracker

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

static size_t WriteCallback(void*,size_t,size_t,std::string*);
void getJson(std::string filename, std::string url, std::string token, std::string& readBuffer); // Gets a json file
std::string getToday(); // Gets the current date in UTC
bool checkRepoCommit(nlohmann::json jsonData, std::string today);
bool checkAllCommit(std::string today, std::string token);
std::vector<std::string> getRepos(std::string filename, std::string &readBuffer, std::string token);

#endif