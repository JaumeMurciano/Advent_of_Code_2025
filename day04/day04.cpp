#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <string>
#include <fstream>
#include <set>
#include <queue>
#include <unordered_map>
#include <map>

int main()
{
    std::ifstream myReadFile{ "day04_input.txt" };
    std::string eachLine{};

    std::vector<std::string> inputMap{};
    int64_t part1{};
    int64_t part2{};

    while (getline(myReadFile, eachLine))
    {
        inputMap.emplace_back(eachLine);
    }

    //used to track if part2 is ended
    bool rollRemoved{ true };
    bool firstRemoval{ true };

    while (rollRemoved)
    {
        std::vector<std::string> newMap{ inputMap }; //part2, take out the rolls removed
        rollRemoved = false;

        for (int32_t i{}; i < inputMap.size(); i++) //search at all map positions
        {
            for (int32_t j{}; j < inputMap[0].size(); j++)
            {
                if (inputMap[i][j] != '@') { continue; } //if current pos is not a roll, skip it
                int32_t count{};
                for (int row{ -1 }; row <= 1; row++) //search at the 8 neighbours
                {
                    for (int col{ -1 }; col <= 1; col++)
                    {
                        if (row == 0 && col == 0) { continue; } //discard invalid and own positions
                        if (i + row < 0 || i + row == inputMap.size() || j + col < 0 || j + col == inputMap[0].size()) { continue; }
                        if (inputMap[i + row][j + col] == '@') { count++; }
                    }
                }
                if (count < 4) //if there are 4 or more rolls, remove the roll
                {
                    if (firstRemoval) { part1++; }
                    part2++;
                    rollRemoved = true;
                    newMap[i][j] = '.';

                }
            }
        }
        inputMap = newMap;
        firstRemoval = false;
    }
    std::cout << "Part 1 result is: " << part1 << '\n';
    std::cout << "Part 2 result is: " << part2;
}