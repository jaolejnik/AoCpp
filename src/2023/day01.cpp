#include "../utils/io.h"

#include <iostream>
#include <regex>
#include <unordered_map>

int part1(const StringVector &calibration_document)
{
    int total_sum = 0;
    const std::regex re("\\d");

    for (const auto &line : calibration_document)
    {
        std::smatch tens_match;
        std::match_results<std::string::const_reverse_iterator> ones_match;

        std::regex_search(line.begin(), line.end(), tens_match, re);
        std::regex_search(line.rbegin(), line.rend(), ones_match, re);

        total_sum += std::stoi(tens_match.str() + ones_match.str());
    }

    return total_sum;
}

int part2(const StringVector &calibration_document)
{
    int total_sum = 0;
    const std::regex re("one|two|three|four|five|six|seven|eight|nine|\\d");

    std::unordered_map<std::string, int> digit_map;
    digit_map["one"]   = 1;
    digit_map["two"]   = 2;
    digit_map["three"] = 3;
    digit_map["four"]  = 4;
    digit_map["five"]  = 5;
    digit_map["six"]   = 6;
    digit_map["seven"] = 7;
    digit_map["eight"] = 8;
    digit_map["nine"]  = 9;
    digit_map["1"]     = 1;
    digit_map["2"]     = 2;
    digit_map["3"]     = 3;
    digit_map["4"]     = 4;
    digit_map["5"]     = 5;
    digit_map["6"]     = 6;
    digit_map["7"]     = 7;
    digit_map["8"]     = 8;
    digit_map["9"]     = 9;

    for (const auto &line : calibration_document)
    {
        std::smatch match;
        std::string first_digit = "";
        std::string last_digit  = "";
        std::string l           = line;

        while (std::regex_search(l, match, re))
        {
            if (first_digit == "")
                first_digit = match.str();
            last_digit = match.str();
            // remove the two first letters to allow for overlaps like: twone, sevenine, etc
            l = match.str().substr(1) + match.suffix().str();
        }

        total_sum += 10 * digit_map[first_digit] + digit_map[last_digit];
    }

    return total_sum;
}

int main()
{
    StringVector calibration_document = read_input_vector_string(__FILE__);

    std::cout << "Part 1: " << part1(calibration_document) << "\n";
    std::cout << "Part 2: " << part2(calibration_document) << "\n";

    return 0;
}
