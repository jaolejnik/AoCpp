#pragma once

#include <string>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

std::string get_input_path(const std::string &current_file)
{
    fs::path cpp_path = current_file;

    std::string day = cpp_path.filename().stem().string();
    std::string year = cpp_path.parent_path().filename();

    return "input/" + year + "/" + day + ".in";
}

std::string read_input_single_string(const std::string &current_file)
{
    std::string input_file = get_input_path(current_file);
    std::ifstream myfile(input_file);
    std::string input_string;

    if (myfile.is_open())
        std::getline(myfile, input_string);

    myfile.close();

    return input_string;
}
