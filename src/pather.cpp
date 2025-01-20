#include "..\\include\\tracker.hpp"
#include <filesystem>
#include <vector>

std::string fix_path(const std::string& relative_path) {
    // The current path
    std::filesystem::path current_path = std::filesystem::current_path(); 

    // Turns the path into a string
    std::string current_path_str = current_path.string();

    // src time // Edits and removes the src
    size_t src_pos = current_path_str.find("src"); // Checks for src
    if (src_pos != std::string::npos) { // If it is in src folder
        current_path_str = current_path_str.substr(0, src_pos); // Remove the src part from the path
    }

    // Bin time // Edits and removes the bin
    size_t bin_pos = current_path_str.find("bin"); // Checks for bin
    if (bin_pos != std::string::npos) { // If it is in bin folder
        current_path_str = current_path_str.substr(0, bin_pos); // Remove the bin part from the path
    }

    // Returns the better path
    return (std::filesystem::path(current_path_str) / relative_path).string(); 
}