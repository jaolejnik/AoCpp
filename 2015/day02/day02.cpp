#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>

std::vector<std::vector<int>> parse_input(const char *filename)
{
    std::vector<std::vector<int>> parsed_data;
    std::string line;
    std::ifstream inputfile(filename);

    if (!inputfile.is_open())
        return parsed_data;

    while (getline(inputfile, line))
    {
        std::stringstream line_ss(line);
        std::string segment;
        std::vector<int> values;

        while (getline(line_ss, segment, 'x'))
            values.push_back(std::stoi(segment));

        std::sort(values.begin(), values.end());
        parsed_data.push_back(values);
    }

    inputfile.close();

    return parsed_data;
}

std::vector<std::vector<int>> calculate_dimensions(std::vector<std::vector<int>> data)
{
    std::vector<std::vector<int>> dimensions;

    for (auto &entry : data)
    {
        std::vector<int> sides;

        for (int i = 0; i < entry.size() - 1; i++)
        {
            int j = i + 1;
            while (j < entry.size())
            {
                sides.push_back(entry[i] * entry[j]);
                j++;
            }
        }

        dimensions.push_back(sides);
    }

    return dimensions;
}

int calculate_total_paper(std::vector<std::vector<int>> dimensions)
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

int calculate_total_ribbon(std::vector<std::vector<int>> data)
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

int part1(std::vector<std::vector<int>> data)
{
    std::vector<std::vector<int>> dimensions = calculate_dimensions(data);
    return calculate_total_paper(dimensions);
}

int part2(std::vector<std::vector<int>> data)
{
    return calculate_total_ribbon(data);
}

int main()
{
    std::vector<std::vector<int>> data = parse_input("input");

    std::cout << part1(data) << std::endl;
    std::cout << part2(data) << std::endl;

    return 0;
}
