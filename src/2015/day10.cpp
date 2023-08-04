#include "../utils/io.h"

#include <iostream>

std::string looknsay(const std::string &str)
{
    std::string result_str;
    int count = 0;

    for (auto it = std::begin(str); it != std::end(str); ++it)
    {
        ++count;

        if (*it != *(it + 1) || it == std::end(str) - 1)
        {
            result_str += std::to_string(count);
            result_str += *it;
            count = 0;
        }
    }

    return result_str;
}

int main()
{
    std::string result = read_input_single_string(__FILE__);

    for (int i = 0; i < 50; ++i)
    {
        if (i == 40)
            std::cout << "Part 1: " << result.size() << "\n";
        result = looknsay(result);
    }

    std::cout << "Part 2: " << result.size() << "\n";

    return 0;
}
