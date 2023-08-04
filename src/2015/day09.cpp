#include "../utils/io.h"

#include <iostream>
#include <unordered_map>
#include <random>
#include <algorithm>

using CityMap = std::unordered_map<std::string, std::unordered_map<std::string, int>>;

CityMap init_city_map(const StringVector2D &input)
{
    CityMap cm;

    for (const auto &line : input)
    {
        auto &from = line[0];
        auto &to = line[2];
        auto distance = std::stoi(line[4]);

        cm[from][to] = distance;
        cm[to][from] = distance;
    }

    return cm;
}

int route_total_distance(const CityMap &city_map, const StringVector &route)
{
    int total_distance = 0;

    for (auto it = std::begin(route); it != std::end(route) - 1; ++it)
        total_distance += city_map.at(*it).at(*(it + 1));

    return total_distance;
}

int main()
{
    auto input = read_input_2D_vector_string(__FILE__, ' ');
    CityMap city_map = init_city_map(input);

    int min_distance = INT32_MAX;
    int max_distance = 0;
    StringVector cities;
    for (const auto &city : city_map)
        cities.push_back(city.first);

    do
    {
        int distance = route_total_distance(city_map, cities);

        min_distance = std::min(min_distance, distance);
        max_distance = std::max(max_distance, distance);
    } while (std::next_permutation(std::begin(cities), std::end(cities)));

    std::cout << "Part 1: " << min_distance << "\n";
    std::cout << "Part 2: " << max_distance << "\n";

    return 0;
}
