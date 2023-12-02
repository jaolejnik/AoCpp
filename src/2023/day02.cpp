#include "../utils/io.h"

#include <iostream>
#include <sstream>

struct Game
{
    int id = 0;
    int r  = 0;
    int g  = 0;
    int b  = 0;
};

int part1(const std::vector<Game> &games)
{
    Game max_cubes{0, 12, 13, 14};
    int possible_game_sum = 0;

    for (const Game &game : games)
    {
        if (game.r <= max_cubes.r && game.g <= max_cubes.g && game.b <= max_cubes.b)
            possible_game_sum += game.id;
    }

    return possible_game_sum;
}

int part2(const std::vector<Game> &games)
{
    int power_sum = 0;

    for (const Game &game : games)
        power_sum += game.r * game.g * game.b;

    return power_sum;
}

int main()
{
    auto input = read_input_vector_string(__FILE__);

    std::vector<Game> games;
    for (const auto &line : input)
    {
        // TODO could reading this input be done more elegantly?
        std::string discard, game_id, round;
        std::stringstream line_ss(line);

        line_ss >> discard >> game_id;
        game_id.pop_back(); // delete ":"

        Game game;
        game.id = std::stoi(game_id);

        while (std::getline(line_ss, round, ';'))
        {
            std::string cubes;
            std::stringstream round_ss(round);

            while (std::getline(round_ss, cubes, ','))
            {
                int count;
                std::string color;
                std::stringstream cubes_ss(cubes);

                cubes_ss >> count >> color;

                if (color == "red")
                    game.r = std::max(game.r, count);
                else if (color == "green")
                    game.g = std::max(game.g, count);
                else //(color == "blue"):
                    game.b = std::max(game.b, count);
            }
        }

        games.push_back(game);
    }

    std::cout << "Part 1: " << part1(games) << "\n";
    std::cout << "Part 2: " << part2(games) << "\n";

    return 0;
}
