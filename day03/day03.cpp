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
    std::ifstream myReadFile{ "day03_input.txt" };
    std::string eachLine{};

    int64_t part1{};
    int64_t part2{};

    while (getline(myReadFile, eachLine))
    {
        //part1:
        int64_t firstNum{ 0 };      //store the first two digits
        int64_t secondNum{ 0 };

        std::array<int64_t, 12> part2Number{}; //for part 2

        for (std::size_t i{ 0 }; i < eachLine.size(); i++)
        {
            if (eachLine[i] - '0' > firstNum && i < eachLine.size() - 1)    //if current digit is greater than my first digit and there is room for filling the second, change it
            {
                firstNum = eachLine[i] - '0';
                secondNum = eachLine[i + 1] - '0';
            }
            else if (eachLine[i] - '0' > secondNum)                         //else, try to make the second digit greater
            {
                secondNum = eachLine[i] - '0';
            }

            //part2
            for (int64_t j{}; j < part2Number.size(); j++)
            {
                if (eachLine[i] - '0' > part2Number[j] && eachLine.size() - i >= part2Number.size() - j)    //if the current digit is greater than any digit (starting from the first) and there is room to fill all the rest, increase it
                {
                    part2Number[j] = eachLine[i] - '0';
                    for (int64_t k{ j + 1 }; k < part2Number.size(); k++)
                    {
                        part2Number[k] = 0;
                    }
                    break;
                }
            }

        }
        part1 += firstNum * 10 + secondNum; //build part 1 number and add it to the result

        int64_t part2int{};                 //build part 2 number and add it to the result
        for (std::size_t i{}; i < part2Number.size(); i++)
        {
            part2int += part2Number[i] * pow(10, part2Number.size() - i - 1);
        }
        part2 += part2int;
    }

    std::cout << "The answer for part 1 is: " << part1 << '\n';
    std::cout << "The answer for part 2 is: " << part2;
    return 0;
}