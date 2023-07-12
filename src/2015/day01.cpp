#include "../utils/io.h"

#include <iostream>

int part1(const std::string &input)
{
    int level = 0;

    for (const char &c : input)
        level += c == '(' ? 1 : -1;

    return level;
}

int part2(const std::string &input)
{
    int level = 0;
    int instruction = 1;

    for (const char &c : input)
    {
        level += c == '(' ? 1 : -1;

        if (level == -1)
            break;

        instruction++;
    }

    return instruction;
}

int main()
{
    std::string input = read_input_single_string(__FILE__);

    std::cout << "Part 1: " << part1(input) << "\n";
    std::cout << "Part 2: " << part2(input) << "\n";

    return 0;
}
