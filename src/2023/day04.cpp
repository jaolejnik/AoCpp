#include "../utils/io.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>

struct ScratchCard
{
    int id             = 0;
    int match_count    = 0;
    int instance_count = 1;
};

int part1(const std::vector<ScratchCard> &scratch_cards)
{
    int total_points = 0;

    for (const auto &scratch_card : scratch_cards)
    {
        if (scratch_card.match_count > 0)
            total_points += std::pow(2, scratch_card.match_count - 1);
    }

    return total_points;
}

int part2(std::vector<ScratchCard> &scratch_cards)
{
    int total_instances = 0;

    for (auto &scratch_card : scratch_cards)
    {
        total_instances += scratch_card.instance_count;

        for (int i = 1; i <= scratch_card.match_count; ++i)
            scratch_cards[scratch_card.id + i - 1].instance_count += scratch_card.instance_count;
    }

    return total_instances;
}

int main()
{
    std::vector<ScratchCard> scratch_cards;

    auto input = read_input_vector_string(__FILE__);
    for (const auto &line : input)
    {
        std::string str;
        std::stringstream line_ss(line);
        std::vector<int> numbers;
        ScratchCard scratch_card;

        line_ss >> str >> str; // discard "Card" and get id
        str.pop_back();

        scratch_card.id = std::stoi(str);

        while (line_ss >> str && str != "|")
            numbers.push_back(std::stoi(str));

        while (line_ss >> str)
        {
            int winnning_number = std::stoi(str);
            if (std::find(numbers.begin(), numbers.end(), winnning_number) != numbers.end())
                scratch_card.match_count++;
        }

        scratch_cards.push_back(scratch_card);
    }

    std::cout << "Part 1: " << part1(scratch_cards) << "\n";
    std::cout << "Part 2: " << part2(scratch_cards) << "\n";

    return 0;
}
