// Time Zone Functions
// Andrew Roddy
// 9/26/24

#pragma once
#ifndef tzone
#define tzone

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


std::tm getLocal(const std::string& utcTime);
std::time_t setUTC(struct std::tm *tm);
std::string getToday();
std::string convertTZ(const std::string& utcTime, int timeZoneOffset);
int getTZ(const std::string& timeZone);

#endif