#include "../utils/io.h"

#include <iostream>
#include <algorithm>
#include <regex>

int part1(const StringVector &engine_schematic)
{
    const std::regex re("[^A-Za-z0-9\\.\\n]");
    const int max_y     = engine_schematic.size();
    const int max_x     = engine_schematic[0].size();
    int part_number_sum = 0;

    // std::cout << "X: 0-" << max_x << " Y: 0-" << max_y << "\n";
    int start = -1;

    for (int y = 0; y < max_y; ++y)
    {
        for (int x = 0; x < max_x; ++x)
        {
            bool start_has_value  = start >= 0;
            bool last_char_in_row = x == max_x - 1;
            bool is_digit         = std::isdigit(engine_schematic[y][x]);

            if (!start_has_value && is_digit)
                start = x;

            if (start_has_value && (!is_digit or last_char_in_row))
            {
                int length         = last_char_in_row ? x + 1 - start : x - start;
                std::string number = engine_schematic[y].substr(start, length);

                int top_bot_start  = std::clamp(start - 1, 0, max_x);
                int top_bot_end    = std::clamp(start + length + 1, 0, max_x);
                int top_bot_length = top_bot_end - top_bot_start;

                std::string left   = start - 1 >= 0 ? engine_schematic[y].substr(start - 1, 1) : "";
                std::string right  = start + length + 1 < max_x ? engine_schematic[y].substr(start + length, 1) : "";
                std::string top    = y - 1 >= 0 ? engine_schematic[y - 1].substr(top_bot_start, top_bot_length) : "";
                std::string bottom = y + 1 < max_x ? engine_schematic[y + 1].substr(top_bot_start, top_bot_length) : "";

                if (std::regex_search(left + top + right + bottom, re))
                    part_number_sum += std::stoi(number);

                start = -1;
            }
        }
    }
    return part_number_sum;
}

int part2(const StringVector &engine_schematic)
{
    const std::regex re("\\d+");
    const int max_y    = engine_schematic.size();
    const int max_x    = engine_schematic[0].size();
    int gear_ratio_sum = 0;

    for (int y = 0; y < max_y; ++y)
    {
        for (int x = 0; x < max_x; ++x)
        {
            if (engine_schematic[y][x] != '*')
                continue;

            int min_adj_x    = std::max(x - 3, 0);
            int max_adj_x    = std::min(x + 3, max_x - 1);
            int left_length  = x - min_adj_x;
            int right_length = max_adj_x - x;

            std::string left   = "";
            std::string top    = "";
            std::string right  = "";
            std::string bottom = "";

            for (int i = -1; i <= 1; ++i)
            {
                if (y + i < 0 || y + i >= max_y)
                    continue;

                std::string *adjacent_field = &top;
                if (i == 0)
                    adjacent_field = &left;
                if (i == 1)
                    adjacent_field = &bottom;

                for (int j = 1; j <= left_length; ++j)
                {
                    const char c = engine_schematic[y + i][x - j];
                    adjacent_field->insert(0, &c, 1);

                    if (!std::isdigit(c))
                        break;
                }

                if (i == 0)
                    adjacent_field = &right;
                else
                    *adjacent_field += engine_schematic[y + i][x];

                for (int j = 1; j <= right_length; ++j)
                {
                    const char c = engine_schematic[y + i][x + j];

                    *adjacent_field += c;

                    if (!std::isdigit(c))
                        break;
                }
            }

            std::smatch part_number_match;
            std::string adjacent_fields = left + "." + top + "." + right + "." + bottom;
            int gear_ratio              = 1;
            int part_number_count       = 0;

            while (std::regex_search(adjacent_fields, part_number_match, re))
            {
                gear_ratio *= std::stoi(part_number_match.str());
                ++part_number_count;
                adjacent_fields = part_number_match.suffix();
            }

            if (part_number_count == 2)
                gear_ratio_sum += gear_ratio;
        }
    }

    return gear_ratio_sum;
}

int main()
{
    auto engine_schematic = read_input_vector_string(__FILE__);

    std::cout << "Part 1: " << part1(engine_schematic) << "\n";
    std::cout << "Part 2: " << part2(engine_schematic) << "\n";

    return 0;
}
