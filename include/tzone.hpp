// Time Zone Functions
// Andrew Roddy
// 9/26/24

#pragma once
#ifndef tzone
#define tzone

#include <iostream>
#include <string>
#include <ctime> // Gets today's time

std::tm getLocal(const std::string& utcTime);
std::string convertTZ(const std::string& utcTime, int timeZoneOffset);
int getTZ(const std::string& timeZone);

#endif