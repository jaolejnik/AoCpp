#include "../utils/io.h"

#include <iostream>
#include <unordered_map>
#include <algorithm>

enum HandType
{
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_KIND,
    FULL_HOUSE,
    FOUR_KIND,
    FIVE_KIND
};

struct Hand
{
    std::string cards;
    std::unordered_map<char, int> card_count_map;
    int bid;
    int type;
};

std::unordered_map<char, int> count_cards(const std::string &cards)
{
    std::unordered_map<char, int> card_count_map;

    for (char card : cards)
    {
        if (card_count_map.find(card) == card_count_map.end())
            card_count_map[card] = 1;
        else
            card_count_map[card] += 1;
    }

    return card_count_map;
}

int card_to_strength(const char card, bool jokers = false)
{
    if (50 <= card && card <= 57)
        return card - '0';

    switch (card)
    {
    case 'T':
        return 10;
    case 'J':
        return jokers ? 1 : 11;
    case 'Q':
        return 12;
    case 'K':
        return 13;
    case 'A':
        return 14;
    default:
        return 0; // should never happen
    }
}

int identify_hand_type(const std::unordered_map<char, int> &card_count_map)
{
    int card_types = card_count_map.size();

    if (card_types == 1)
        return FIVE_KIND;

    if (card_types == 5)
        return HIGH_CARD;

    std::string count_str = "";
    for (const auto &card_count : card_count_map)
        count_str += '0' + card_count.second;
    std::sort(count_str.begin(), count_str.end());

    if (card_types == 2)
    {
        if (count_str == "14")
            return FOUR_KIND;
        else // (count_str == "23")
            return FULL_HOUSE;
    }

    if (card_types == 3)
    {
        if (count_str == "113") // three kind
            return THREE_KIND;
        else // (count_str == "122")
            return TWO_PAIR;
    }

    return ONE_PAIR; // (card_types == 4 && count_str == "1112")
}

int identify_hand_type_jokers(const std::unordered_map<char, int> &card_count_map)
{
    if (card_count_map.find('J') == card_count_map.end())
        return identify_hand_type(card_count_map);

    int card_types = card_count_map.size();

    // 5 jokers OR
    // 4 kind + 1 joker (4 jokers + 1 distinct) OR
    // 3 kind + 2 jokers (3 jokers + 2 kind)
    if (card_types < 3)
        return FIVE_KIND;

    std::string count_str = "";
    for (const auto &card_count : card_count_map)
        count_str += '0' + card_count.second;
    std::sort(count_str.begin(), count_str.end());

    if (card_types == 3)
    {
        // 2 distinct + 3 jokers OR
        // 3 kind + 1 distinct + 1 joker OR
        // 2 kind + 1 distinct + 2 jokers
        if (count_str == "113" || card_count_map.at('J') == 2)
            return FOUR_KIND;
        else // 2 kind + 2 kind + 1 joker
            return FULL_HOUSE;
    }

    // 2 distincts + 2 kind + 1 joker
    // 3 distincts + 2 jokers
    if (card_types == 4)
        return THREE_KIND;

    return ONE_PAIR; // 4 distinct + 1 joker
}

int part1(std::vector<Hand> &hands)
{
    int total_winnings = 0;

    std::sort(hands.begin(), hands.end(), [](const Hand &a, const Hand &b) {
        if (a.type == b.type)
        {
            for (int i = 0; i < 5; ++i)
            {
                int a_card_strength = card_to_strength(a.cards[i]);
                int b_card_strength = card_to_strength(b.cards[i]);

                if (a_card_strength != b_card_strength)
                    return a_card_strength < b_card_strength;
            }
        }

        return a.type < b.type;
    });

    for (size_t i = 0; i < hands.size(); ++i)
        total_winnings += hands[i].bid * (i + 1);

    return total_winnings;
}

int part2(std::vector<Hand> &hands)
{
    for (auto &hand : hands)
        hand.type = identify_hand_type_jokers(hand.card_count_map);

    int total_winnings = 0;

    std::sort(hands.begin(), hands.end(), [](const Hand &a, const Hand &b) {
        if (a.type == b.type)
        {
            for (int i = 0; i < 5; ++i)
            {
                int a_card_strength = card_to_strength(a.cards[i], true);
                int b_card_strength = card_to_strength(b.cards[i], true);

                if (a_card_strength != b_card_strength)
                    return a_card_strength < b_card_strength;
            }
        }

        return a.type < b.type;
    });

    for (size_t i = 0; i < hands.size(); ++i)
        total_winnings += hands[i].bid * (i + 1);

    return total_winnings;
}

int main()
{
    auto input = read_input_2D_vector_string(__FILE__, ' ');

    std::vector<Hand> hands;
    hands.reserve(input.size());

    for (const auto &line : input)
    {
        std::string cards                            = line[0];
        std::unordered_map<char, int> card_count_map = count_cards(cards);
        int bid                                      = std::stoi(line[1]);
        int type                                     = identify_hand_type(card_count_map);

        hands.emplace_back(cards, card_count_map, bid, type);
    }

    std::cout << "Part 1: " << part1(hands) << "\n";
    std::cout << "Part 2: " << part2(hands) << "\n";

    return 0;
}
