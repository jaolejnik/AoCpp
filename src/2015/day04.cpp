#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <openssl/md5.h>

// ! Remember to compile with -lcrypto flag

// Source for MD5 hash using OpenSSL:
// https://terminalroot.com/how-to-generate-md5-hash-with-cpp-and-openssl/
std::string md5(const std::string &str)
{
    unsigned char hash[MD5_DIGEST_LENGTH];

    MD5_CTX md5;
    MD5_Init(&md5);
    MD5_Update(&md5, str.c_str(), str.size());
    MD5_Final(hash, &md5);

    std::stringstream ss;

    for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }

    return ss.str();
}

std::string get_input_string(const std::string &filename)
{
    std::string line;
    std::ifstream myfile(filename);

    if (myfile.is_open())
        std::getline(myfile, line);

    myfile.close();

    return line;
}

int find_number(const std::string &key, const std::string &match, int min = 0, int max = INT32_MAX)
{
    int i = min;
    int lenght = match.size();

    while (md5(key + std::to_string(i)).substr(0, lenght) != match)
    {
        i++;

        if (i > max)
            return -1;
    }

    return i;
}

int part1(const std::string &key)
{
    return find_number(key, "00000");
}

int part2(const std::string &key)
{
    return find_number(key, "000000");
}

int main()
{
    std::string key = get_input_string("input/2015/day04.in");

    std::cout << "Part 1: " << part1(key) << std::endl;
    std::cout << "Part 2: " << part2(key) << std::endl;

    return 0;
}
