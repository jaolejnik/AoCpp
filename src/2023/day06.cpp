#include "../utils/io.h"

#include <iostream>
#include <cmath>

struct RaceData
{
    int64_t time;
    int64_t record_distance;
};

int64_t count_winning_configs(const RaceData &race)
{
    // this is just a quadratic inequality

    float discriminant = race.time * race.time - 4.0f * race.record_distance;
    float t1           = (race.time - std::sqrt(discriminant)) / 2.0f;
    float t2           = (race.time + std::sqrt(discriminant)) / 2.0f;

    // Had to get a small hint on gettig the range correctly
    // Examples:
    //      round up   (5.30 - 1) to get 5
    //      round down (1.69 + 1) to get 2
    //
    //      round up   (20 - 1) to get 19
    //      round down (10 + 1) to get 11
    //
    // this way we get inclusive ranges for both int and float results of t1, t2

    return std::ceil(t2 - 1) - std::floor(t1 + 1) + 1;
}

int part1(const std::vector<RaceData> &races)
{
    int records_product = 1;
    for (auto &race : races)
        records_product *= count_winning_configs(race);

    return records_product;
}

int main()
{
    std::vector<RaceData> races;
    RaceData big_race;

    auto input = read_input_vector_string(__FILE__);

    std::string str_big_time     = "";
    std::string str_big_distance = "";
    std::string str_num;
    std::stringstream line_ss(input[0]);
    line_ss >> str_num; // discard "Time:"

    while (line_ss >> str_num)
    {
        str_big_time += str_num;
        races.push_back({std::stoi(str_num), 0});
    }

    line_ss.str(input[1]);
    line_ss.clear();
    line_ss >> str_num; // discard "Distance:"

    for (auto &race : races)
    {
        line_ss >> str_num;
        str_big_distance += str_num;
        race.record_distance = std::stoi(str_num);
    }

    big_race.time            = std::stoll(str_big_time);
    big_race.record_distance = std::stoll(str_big_distance);

    std::cout << "Part 1: " << part1(races) << "\n";

    std::cout << "Part 2: " << count_winning_configs(big_race) << "\n";

    return 0;
}
