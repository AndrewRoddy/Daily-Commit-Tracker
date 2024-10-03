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

#include "tzone.hpp"

using std::cout; using std::cin; using std::endl; using std::string;

// Gets currrent time // Copied from Internet
std::tm getLocal(const std::string& utcTime) {
    std::tm timeStruct = {};
    std::istringstream ss(utcTime);
    ss >> std::get_time(&timeStruct, "%Y-%m-%dT%H:%M:%SZ");

    // Set the tm_isdst to 0 to avoid daylight saving time adjustments
    timeStruct.tm_isdst = 0;
    return timeStruct;
}

// Converts current time to UTC // Copied from Internet
std::time_t setUTC(struct std::tm *tm) {
    std::time_t ret = std::mktime(tm);
    return ret - _timezone; // Adjust for the local time zone difference
}

// Converts UTC times to selected time zone // Copied from the Internet
std::string convertTZ(const std::string& utcTime, int timeZoneOffset) {
    std::tm utcTm = getLocal(utcTime); // Parse the input UTC time string
    std::time_t utcTimeT = setUTC(&utcTm);  // setUTC() treats time as UTC
    utcTimeT += (timeZoneOffset * 3600); // Adjust the time for the given time zone offset (hours to seconds)
    std::tm* localTm = std::gmtime(&utcTimeT); // Convert back to std::tm (this gives time in UTC again)

    std::ostringstream oss; // Converts adjusted time to string
    oss << std::put_time(localTm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

// Gets time zone value from text string // Copied from Internet
int getTZ(const std::string& timeZone) {
    // Map of common time zones to their offsets from UTC
    std::unordered_map<std::string, int> timeZoneOffsets = {
        {"UTC", 0},
        {"EDT", -4}, // Eastern Daylight Time
        {"EST", -5},
        {"CDT", -5}, // Central Daylight Time
        {"CST", -6},
        {"MDT", -6}, // Mountain Daylight Time
        {"MST", -7},
        {"PDT", -7},  // Pacific Daylight Time
        {"PST", -8}
    };

    if (timeZoneOffsets.find(timeZone) != timeZoneOffsets.end()) {
        return timeZoneOffsets[timeZone];
    } else {
        std::cout << "Unknown time zone: " << timeZone << std::endl;
        return 0; // Default to UTC if unknown
    }
}
