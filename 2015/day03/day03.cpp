#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>

std::string get_input_string(const char *filename)
{
    std::string line;
    std::ifstream myfile(filename);

    if (myfile.is_open())
        getline(myfile, line);

    myfile.close();

    return line;
}

void move(char const &instruction, int position[])
{
    switch (instruction)
    {
    case '^':
        position[1]++;
        break;
    case 'v':
        position[1]--;
        break;
    case '<':
        position[0]--;
        break;
    case '>':
        position[0]++;
        break;
    }
}

int part1(std::string instructions)
{
    int position[2] = {0, 0};
    std::unordered_map<std::string, int> visited_positions;

    visited_positions["0,0"] = 1;

    for (char const &instruction : instructions)
    {
        move(instruction, position);
        std::string pos_key = std::to_string(position[0]) + ',' + std::to_string(position[1]);

        if (visited_positions.find(pos_key) == visited_positions.end())
            visited_positions[pos_key] = 1;
        else
            visited_positions[pos_key]++;
    }

    return visited_positions.size();
}

int part2(std::string instructions)
{
    int turn = 0;
    int santa_position[2] = {0, 0};
    int robot_position[2] = {0, 0};
    std::unordered_map<std::string, int> visited_positions;

    visited_positions["0,0"] = 1;

    for (char const &instruction : instructions)
    {
        std::string pos_key;

        if (turn % 2)
        {
            move(instruction, robot_position);
            pos_key = std::to_string(robot_position[0]) + ',' + std::to_string(robot_position[1]);
        }
        else
        {
            move(instruction, santa_position);
            pos_key = std::to_string(santa_position[0]) + ',' + std::to_string(santa_position[1]);
        }

        if (visited_positions.find(pos_key) == visited_positions.end())
            visited_positions[pos_key] = 1;
        else
            visited_positions[pos_key]++;

        turn++;
    }

    return visited_positions.size();
}

int main()
{
    std::string instructions = get_input_string("input");

    std::cout << part1(instructions) << std::endl;
    std::cout << part2(instructions) << std::endl;

    return 0;
}
