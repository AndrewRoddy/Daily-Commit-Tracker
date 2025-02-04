// Gets Tokens
// Andrew Roddy
// 11/10/2024

#pragma once
#ifndef tokens
#define tokens

#include <iostream>
#include <string>

#include <fstream>
#include <filesystem> // Just to check for TOKENS.env
#include <cstdlib>

void token_check();
std::string getTokenPath(); // Gets the correct token path
std::string getToken(); // Gets the token

#endif