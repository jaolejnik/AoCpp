#include "../utils/io.h"

#include <iostream>
#include <sstream>
#include <vector>

std::vector<std::vector<int>> parse_input(const std::string &filename)
{
    std::vector<std::vector<int>> parsed_data;
    std::string line;
    std::ifstream inputfile(filename);

    if (!inputfile.is_open())
        return parsed_data;

    while (std::getline(inputfile, line))
    {
        std::stringstream line_ss(line);
        std::string segment;
        std::vector<int> values;

        while (std::getline(line_ss, segment, 'x'))
            values.push_back(std::stoi(segment));

        std::sort(values.begin(), values.end());
        parsed_data.push_back(values);
    }

    inputfile.close();

    return parsed_data;
}

std::vector<std::vector<int>> calculate_dimensions(const std::vector<std::vector<int>> &data)
{
    std::vector<std::vector<int>> dimensions;

    for (auto &entry : data)
    {
        std::vector<int> sides;
        int size = entry.size();

        for (int i = 0; i < size - 1; i++)
        {
            int j = i + 1;
            while (j < size)
            {
                sides.push_back(entry[i] * entry[j]);
                j++;
            }
        }

        dimensions.push_back(sides);
    }

    return dimensions;
}

int calculate_total_paper(const std::vector<std::vector<int>> &dimensions)
{
    int sum = 0;

    for (auto &sides : dimensions)
    {
        sum += 3 * sides[0];
        sum += 2 * sides[1];
        sum += 2 * sides[2];
    }

    return sum;
}

int calculate_total_ribbon(const std::vector<std::vector<int>> &data)
{
    int sum = 0;

    for (auto &entry : data)
    {
        sum += 2 * entry[0];
        sum += 2 * entry[1];
        sum += entry[0] * entry[1] * entry[2];
    }

    return sum;
}

int part1(const std::vector<std::vector<int>> &data)
{
    std::vector<std::vector<int>> dimensions = calculate_dimensions(data);
    return calculate_total_paper(dimensions);
}

int part2(const std::vector<std::vector<int>> &data)
{
    return calculate_total_ribbon(data);
}

int main()
{
    auto data = parse_input(get_input_path(__FILE__));

    std::cout << "Part 1: " << part1(data) << std::endl;
    std::cout << "Part 2: " << part2(data) << std::endl;

    return 0;
}
