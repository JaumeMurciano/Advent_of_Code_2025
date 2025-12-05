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
	std::ifstream myReadFile("day05_input.txt");
	std::string inputLine{};

	int64_t part1{};
	int64_t part2{};

	std::vector<std::array<int64_t, 2>> validRanges{}; //for part1
	std::vector<std::array<int64_t, 2>> uniqueRanges{}; //for part 2

	bool secondPart{false};
	while (std::getline(myReadFile, inputLine))
	{
		if (inputLine == "") { secondPart = true; continue; } //part1 consists only on storing the numbers and checking if the second part numbers are in any range
		if (!secondPart)
		{
			std::stringstream eachLine{ inputLine };
			std::string eachNum{};
			std::array<int64_t, 2> eachRange{};

			std::getline(eachLine, eachNum, '-');
			eachRange[0] = std::stoll(eachNum);
			std::getline(eachLine, eachNum, '-');
			eachRange[1] = std::stoll(eachNum);
			validRanges.emplace_back(eachRange);
		}
		else
		{
			int64_t currentNumber{std::stoll(inputLine)};
			for (std::array<int64_t, 2>&eachRange : validRanges)
			{
				if (eachRange[0] <= currentNumber && currentNumber <= eachRange[1])
				{
					part1++;
					break;
				}
			}
		}
	}

	//part2
	std::queue<std::array<int64_t, 2>> pairQueue{}; //this queue stores all the sub-pairs created by splitting the current pair
	for (std::size_t i{}; i < validRanges.size(); i++)
	{
		pairQueue.emplace(validRanges[i]);			//the current pair is emplaced
		while (!pairQueue.empty())
		{
			std::array<int64_t,2> currentPair{pairQueue.front()};
			pairQueue.pop();
			bool pairAlreadyCounted{ false };		//bool to signal that current pair is already completely covered
			for (std::size_t j{}; j < uniqueRanges.size(); j++)
			{
				if (currentPair[0] >= uniqueRanges[j][0] && currentPair[1] <= uniqueRanges[j][1]) { pairAlreadyCounted = true; }	//pair is already counted, skip it 
				else if (currentPair[0] < uniqueRanges[j][0] && currentPair[1] > uniqueRanges[j][1])	//pair contains an already counted range, emplace the greater part and keep with the lower one
				{
					std::array<int64_t, 2> newPair{ uniqueRanges[j][1] + 1, currentPair[1] };
					pairQueue.emplace(newPair);
					currentPair[1] = uniqueRanges[j][0] - 1;
				}
				else if (currentPair[0] < uniqueRanges[j][0] && currentPair[1] >= uniqueRanges[j][0]) { currentPair[1] = uniqueRanges[j][0] - 1; } //the end of the pair is contained in the pair being checked
				else if (currentPair[0] <= uniqueRanges[j][1] && currentPair[1] > uniqueRanges[j][1]) { currentPair[0] = uniqueRanges[j][1] + 1; } //the start of the pair is contained in the pair being checked
				if (currentPair[0] > currentPair[1]) { continue; }	//pair is fully contained by two distinct pairs

			}
			if (pairAlreadyCounted) { continue; }
			part2 += currentPair[1] - currentPair[0] + 1;			//add the pair to part 2 and to the list
			uniqueRanges.emplace_back(currentPair);
		}
	}

	std::cout << "Part 1 result is: " << part1 << "\n";
	std::cout << "Part 2 result is: " << part2;
}