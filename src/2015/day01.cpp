#include <iostream>
#include <fstream>

std::string get_input_string(const char *filename)
{
    std::string line;
    std::ifstream myfile(filename);

    if (myfile.is_open())
        std::getline(myfile, line);

    myfile.close();

    return line;
}

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
    std::string puzzle_input = get_input_string("input/2015/day01.in");

    std::cout << "Part 1: " << part1(puzzle_input) << std::endl;
    std::cout << "Part 2: " << part2(puzzle_input) << std::endl;

    return 0;
}
