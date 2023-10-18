#include "../utils/io.h"

#include <iostream>

void increment_password(std::string &password)
{
    auto letter_rit = std::rbegin(password);

    while (*letter_rit == 'z')
    {
        *letter_rit = 'a';
        letter_rit += 1; // move iterator
    }

    if (letter_rit == std::rend(password))
        password.insert(0, "a");
    else
        *letter_rit += 1; // increase ascii value
}

bool has_increasing_letters(const std::string &password)
{
    for (size_t i = 0; i < password.size() - 2; ++i)
    {
        if ((password[i + 1] - password[i + 0] == 1) &&
            (password[i + 2] - password[i + 1] == 1))
        {
            return true;
        }
    }

    return false;
}

bool has_not_allowed_letters(const std::string &password)
{
    return password.find_first_of("ilo") != std::string::npos;
}

bool has_nonoverlapping_pair_letters(const std::string &password)
{
    std::string pairs = "";

    for (size_t i = 0; i < password.size() - 1; ++i)
    {
        if (password[i] != password[i + 1])
            continue;

        if (pairs.find_first_of(password[i]) == std::string::npos)
            pairs += password[i];
        else
            return false; // overlap
    }

    return pairs.size() >= 2;
}

std::string update_password(const std::string &password)
{
    std::string new_password = password;

    do
    {
        increment_password(new_password);
        // for longer password it would be better to combine these 3 check to avoid multiple iterations,
        // but since it's quite short and it's not gonna grow, I just left it as it is to make it more readable
    } while (!(has_increasing_letters(new_password) &&
               !has_not_allowed_letters(new_password) &&
               has_nonoverlapping_pair_letters(new_password)));

    return new_password;
}

int main()
{
    std::string password = read_input_single_string(__FILE__);

    password = update_password(password);
    std::cout << "Part 1: " << password << "\n";
    password = update_password(password);
    std::cout << "Part 2: " << password << "\n";

    return 0;
}
