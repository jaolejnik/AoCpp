#include <iostream>
#include <fstream>

using namespace std;

string get_input_string(const char *filename)
{
    string line;
    ifstream myfile(filename);

    if (myfile.is_open())
        getline(myfile, line);

    myfile.close();

    return line;
}

int part1(string input)
{
    int level = 0;

    for (char const &c : input)
        level += c == '(' ? 1 : -1;

    return level;
}

int part2(string input)
{
    int level = 0;
    int instruction = 1;

    for (char const &c : input)
    {
        level += c == '(' ? 1 : -1;

        if (level == -1)
            break;

        instruction++;
    }

    return instruction;
}

int main()
{
    string puzzle_input = get_input_string("input");
    cout << part1(puzzle_input) << endl;
    cout << part2(puzzle_input) << endl;

    return 0;
}
