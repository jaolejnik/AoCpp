#pragma once

#include <string>
#include <fstream>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

using StringVector = std::vector<std::string>;
using StringVector2D = std::vector<std::vector<std::string>>;

std::string get_input_path(const std::string &current_file)
{
    fs::path cpp_path = current_file;

    std::string day = cpp_path.filename().stem().string();
    std::string year = cpp_path.parent_path().filename();

    return "input/" + year + "/" + day + ".in";
}

std::string read_input_single_string(const std::string &current_file)
{
    std::string input_path = get_input_path(current_file);
    std::ifstream input_file(input_path);
    std::string input_string;

    if (input_file.is_open())
        std::getline(input_file, input_string);

    input_file.close();

    return input_string;
}

StringVector read_input_vector_string(const std::string &current_file)
{
    std::string input_path = get_input_path(current_file);
    std::ifstream input_file(input_path);
    std::string line;
    StringVector input_strings;

    while (std::getline(input_file, line))
        input_strings.push_back(line);

    return input_strings;
}

StringVector2D read_input_2D_vector_string(const std::string &current_file, const char separator)
{
    std::string input_path = get_input_path(current_file);
    std::ifstream input_file(input_path);
    std::string line;
    StringVector2D data;

    if (!input_file.is_open())
        return data;

    while (std::getline(input_file, line))
    {
        std::stringstream line_ss(line);
        std::string segment;
        StringVector sv;

        while (std::getline(line_ss, segment, separator))
            sv.push_back(segment);

        data.push_back(sv);
    }

    input_file.close();

    return data;
}
