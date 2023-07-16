#include "../utils/io.h"

#include <iostream>
#include <regex>

int part1(const StringVector &input)
{
    int nice_count = 0;
    std::regex vowels_re("([aeiou].*){3,}");
    std::regex double_re("(.)\\1");
    std::regex substr_re("ab|cd|pq|xy");

    for (const std::string &s : input)
    {
        if (std::regex_search(s, vowels_re) &&
            std::regex_search(s, double_re) &&
            !std::regex_search(s, substr_re))
            nice_count++;
    }

    return nice_count;
}

int part2(const StringVector &input)
{
    int nice_count = 0;
    std::regex double_double_re("(..).*\\1");
    std::regex surround_re("(.).\\1");

    for (const std::string &s : input)
    {
        if (std::regex_search(s, double_double_re) &&
            std::regex_search(s, surround_re))
            nice_count++;
    }

    return nice_count;
}

int main()
{
    auto input = read_input_vector_string(__FILE__);

    std::cout << "Part 1: " << part1(input) << "\n";
    std::cout << "Part 2: " << part2(input) << "\n";

    return 0;
}
