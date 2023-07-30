#include "../utils/io.h"

#include <iostream>

/*
I could have gotten away with just counting, adding and subtracting chars,
but where's the fun in that.
*/

const std::string decode_str(const std::string &raw_str)
{
    std::string str = "";

    for (auto chr = raw_str.begin() + 1; chr != raw_str.end() - 1; ++chr)
    {
        if (*chr == '\\')
        {
            ++chr; // skip escape '\'

            if (*chr == 'x')
            {
                ++chr; // skip x after '\'

                int ascii_value;
                std::stringstream hex_ss(std::string(chr, chr + 2));
                hex_ss >> std::hex >> ascii_value;
                str += ascii_value;
                ++chr; // skip to the 2nd hex character
                continue;
            }
        }

        str += *chr;
    }

    return str;
}

const std::string encode_str(const std::string &raw_str)
{
    std::string str = "\"";

    for (auto chr = raw_str.begin(); chr != raw_str.end(); ++chr)
    {
        if (*chr == '\\' || *chr == '\"')
            str += "\\";
        str += *chr;
    }

    str += "\"";

    return str;
}

int part1(const StringVector &strings)
{
    int str_char_count = 0;
    int mem_char_count = 0;

    for (const auto &str : strings)
    {
        str_char_count += str.length();
        mem_char_count += decode_str(str).length();
    }

    return str_char_count - mem_char_count;
}

int part2(const StringVector &strings)
{
    int str_char_count = 0;
    int encoded_char_count = 0;

    for (const auto &str : strings)
    {
        str_char_count += str.length();
        encoded_char_count += encode_str(str).length();
    }

    return encoded_char_count - str_char_count;
}

int main()
{
    auto input = read_input_vector_string(__FILE__);

    std::cout << "Part 1: " << part1(input) << "\n";
    std::cout << "Part 2: " << part2(input) << "\n";

    return 0;
}
