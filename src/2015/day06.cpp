#include "../utils/io.h"

#include <iostream>
#include <array>

std::array<int, 2> range_str_to_int(const std::string &range_str)
{
    std::stringstream ss(range_str);
    std::string segment;
    std::array<int, 2> range_int;

    for (int i = 0; i < 2; i++)
    {
        std::getline(ss, segment, ',');
        range_int[i] = std::stoi(segment);
    }

    return range_int;
}

int part1(const std::vector<std::vector<std::string>> &instructions)
{
    std::array<std::array<bool, 1000>, 1000> lights = {{0}};
    int lights_lit = 0;

    for (const auto &instruction : instructions)
    {
        int offset = instruction.size() == 4 ? 1 : 0;
        std::string action = instruction[1 - offset];
        auto xymin = range_str_to_int(instruction[2 - offset]);
        auto xymax = range_str_to_int(instruction[4 - offset]);

        for (int y = xymin[1]; y <= xymax[1]; y++)
        {
            for (int x = xymin[0]; x <= xymax[0]; x++)
            {
                if (action == "on")
                    lights[y][x] = 1;
                else if (action == "off")
                    lights[y][x] = 0;
                else
                    lights[y][x] = !lights[y][x];
            }
        }
    }

    for (int y = 0; y < 1000; y++)
        for (int x = 0; x < 1000; x++)
            lights_lit += lights[y][x];

    return lights_lit;
}

int part2(const std::vector<std::vector<std::string>> &instructions)
{
    std::array<std::array<int, 1000>, 1000> lights = {{0}};
    int lights_brightness = 0;

    for (const auto &instruction : instructions)
    {
        int offset = instruction.size() == 4 ? 1 : 0;
        std::string action = instruction[1 - offset];
        auto xymin = range_str_to_int(instruction[2 - offset]);
        auto xymax = range_str_to_int(instruction[4 - offset]);

        for (int y = xymin[1]; y <= xymax[1]; y++)
        {
            for (int x = xymin[0]; x <= xymax[0]; x++)
            {
                if (action == "on")
                    lights[y][x] += 1;
                else if (action == "off")
                    lights[y][x] -= lights[y][x] > 0 ? 1 : 0;
                else
                    lights[y][x] += 2;
            }
        }
    }

    for (int y = 0; y < 1000; y++)
        for (int x = 0; x < 1000; x++)
            lights_brightness += lights[y][x];

    return lights_brightness;
}

int main()
{
    auto input = read_input_2D_vector_string(__FILE__, ' ');

    std::cout << "Part 1: " << part1(input) << "\n";
    std::cout << "Part 2: " << part2(input) << "\n";

    return 0;
}
