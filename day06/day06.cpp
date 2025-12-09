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

//Note: This problem does not have many commentaries as the complication is to parse the input correctly.

int main()
{
	std::ifstream myReadFile("day06_input.txt");
	std::ifstream secondRead("day06_input.txt");
	std::string inputLine{};
	std::vector<std::vector<uint64_t>> allNumbers{};
	std::vector < std::vector < std::string >> allStrings{};
	std::vector<char> allOperations{};
	std::vector<int32_t> numSizes{};
	uint64_t part1{};
	uint64_t part2{};

	//part1: All numbers are stored in allNumbers vector, and all Operations in allOperations vector
	while (std::getline(myReadFile, inputLine))
	{
		std::stringstream eachLine{inputLine};
		std::string eachNum{};
		std::vector<uint64_t> eachNumLine{};
		int32_t numSize{};
		while (std::getline(eachLine, eachNum, ' '))
		{
			if (eachNum == "") { numSize++;  continue; }
			if (eachNum[0] == '*' || eachNum[0] == '+') {
				if (allOperations.size() > 0) { numSizes.emplace_back(numSize); } //for part2! Store the size of each number. Operations are the aligner
				allOperations.emplace_back(eachNum[0]);
				numSize = 1;
			}
			else { eachNumLine.emplace_back(std::stoull(eachNum)); }
		}
		if (eachNumLine.size() > 0) { allNumbers.emplace_back(eachNumLine); }
		if (allOperations.size() > 0) { numSizes.emplace_back(numSize+1); }
	}
	//Part 1: Calculate the operations
	for (int32_t i{}; i < allOperations.size(); i++)
	{
		if (allOperations[i] == '+') {
			for (int32_t j{}; j < allNumbers.size(); j++) { part1 += allNumbers[j][i]; }
		}
		else if (allOperations[i] == '*') {
			uint64_t numToMultiply{ 1 };
			for (int32_t j{}; j < allNumbers.size(); j++) { numToMultiply *= allNumbers[j][i]; }
			part1 += numToMultiply;
		}
	}

	//part 2: Now store all the string corresponding to the number (including spaces) to ease the alignement
	while (std::getline(secondRead, inputLine))
	{
		if (inputLine[0] == '+' || inputLine[0] == '*') { continue; }
		int32_t currentIndex{};
		int32_t currentSize{};
		std::vector<std::string> eachLineNumbers{};
		while (currentIndex <= inputLine.size())
		{

			eachLineNumbers.emplace_back(inputLine.substr(currentIndex,numSizes[currentSize]));
			currentIndex += numSizes[currentSize] + 1;
			currentSize++;
		}
		allStrings.emplace_back(eachLineNumbers);
	}

	//And finally build all numbers and perform the operations
	for (int32_t i{}; i < allOperations.size(); i++)
	{
		std::vector<uint64_t> allNumbersInLine{};
		for (int32_t digitNum{}; digitNum < allStrings[0][i].size(); digitNum++)
		{
			uint64_t currentNumber{0};
			for (int32_t j{}; j < allNumbers.size(); j++)
			{
				if (allStrings[j][i][digitNum] == ' ') { continue; }
				currentNumber *= 10;
				currentNumber += allStrings[j][i][digitNum] - '0';
			}
			allNumbersInLine.emplace_back(currentNumber);
		}
		if (allOperations[i] == '+') {
			for (int32_t j{}; j < allNumbersInLine.size(); j++) { part2 += allNumbersInLine[j]; }
		}
		else if (allOperations[i] == '*') {
			uint64_t numToMultiply{ 1 };
			for (int32_t j{}; j < allNumbersInLine.size(); j++) { numToMultiply *= allNumbersInLine[j]; }
			part2 += numToMultiply;
		}
	}

	std::cout << "Part 1 result is: " << part1 << "\n";
	std::cout << "Part 2 result is: " << part2;
}