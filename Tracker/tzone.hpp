// Lucky Five library header
// Andrew Roddy
// 9/26/24

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

#pragma once
#ifndef tzone
#define tzone

std::tm getLocal(const std::string& utcTime);
std::string convertTZ(const std::string& utcTime, int timeZoneOffset);
int getTZ(const std::string& timeZone);

#endif