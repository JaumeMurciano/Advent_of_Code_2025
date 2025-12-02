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
#include <cmath>

int main()
{
    std::ifstream readFile{ "day02_input.txt" };
    std::string eachLine{};
    getline(readFile, eachLine);

    std::stringstream inputLine{ eachLine };
    std::string eachNumber{};

    int64_t part1{};
    int64_t part2{};
    std::set<int64_t> allInvalids{};

    while (getline(inputLine, eachNumber, '-'))
    {
        std::string lowerNumber = eachNumber;
        getline(inputLine, eachNumber, ',');
        std::string higherNumber = eachNumber;

        int64_t startingNumber{};
        //assumption that the size of the numbers is not greater than 1 in the input (the input looks like it complies)
        for (int32_t i{ 2 }; i <= higherNumber.size(); i++) //divide the number in n_repeating parts
        {
            if (lowerNumber.size() % i == 0) { startingNumber = std::stoll(lowerNumber.substr(0, lowerNumber.size() / i)); }    //the parts have to match exactly with the size
            else if (higherNumber.size() % i == 0) { startingNumber = pow(10, (higherNumber.size() - 1) / i); }                 //this is for the case that the size of the second number is the lower +1
            else { continue; }                              //does not match!
            int64_t checkingNumber{};                       //this is the number that is going to be checked, and starting number is the one being repeated
            for (int64_t j{}; j < i; j++)
            {
                checkingNumber += startingNumber * pow(10, (static_cast<int64_t>(std::log10(startingNumber)) + 1) * j);
            }

            while (checkingNumber <= std::stoll(higherNumber))
            {
                if (checkingNumber >= std::stoll(lowerNumber)) //check if the number is in bounds
                { 
                    if (allInvalids.find(checkingNumber) == allInvalids.end())  //if not already added
                    {
                        if (i == 2) { part1 += checkingNumber; }    //if the number is divided in only two parts add to part 1
                        part2 += checkingNumber;
                        allInvalids.emplace(checkingNumber);
                    }
                    
                }
                startingNumber++;                               //create the next number to be checked
                checkingNumber = 0;
                for (int64_t j{}; j < i; j++)
                {
                    checkingNumber += startingNumber * pow(10, (static_cast<int64_t>(std::log10(startingNumber)) + 1) * j);
                }
            }
        }
    }
    std::cout << "Part 1 result is: " << part1 << "\n";
    std::cout << "Part 2 result is: " << part2;
}