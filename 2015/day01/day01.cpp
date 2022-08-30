#include <iostream>
#include <fstream>

std::string get_input_string(const char *filename)
{
    std::string line;
    std::ifstream myfile(filename);

    if (myfile.is_open())
        getline(myfile, line);

    myfile.close();

    return line;
}

int part1(std::string input)
{
    int level = 0;

    for (char const &c : input)
        level += c == '(' ? 1 : -1;

    return level;
}

int part2(std::string input)
{
    int level = 0;
    int instruction = 1;

    for (char const &c : input)
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
    std::string puzzle_input = get_input_string("input");
    std::cout << part1(puzzle_input) << std::endl;
    std::cout << part2(puzzle_input) << std::endl;

    return 0;
}
