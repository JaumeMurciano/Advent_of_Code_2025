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
	std::ifstream myReadFile("day01_input.txt");
	std::string inputLine{};

	int64_t part1{};				//tracks the number of times that we end a turn in a 0
	int64_t part2{};				//tracks the number of times where we cross a 0
	int32_t currentPosition{ 50 };	//start at position 50

	while (std::getline(myReadFile, inputLine))
	{
		int32_t prevPos = currentPosition;
		int32_t movingPositions = std::stoi(inputLine.substr(1, inputLine.size() - 1));	//extract the number of positions we are moving
		part2 += movingPositions / 100;			//for part 2: there is no point on entering in moving +100 position caveats, just extract the 0s crossed
		movingPositions %= 100;
		if (inputLine[0] == 'R') { currentPosition += movingPositions; }	//add or subtract the positons
		if (inputLine[0] == 'L') { currentPosition -= movingPositions; }
		if (currentPosition > 100) { part2++; }	//if we are crossing a 0 because we are going over a 100, add it
		currentPosition %= 100;					//normalize the number over 100%
		if (currentPosition < 0)				//if the number is negative and the previous position is not 0, we have crossed one 0
		{ 
			if (prevPos != 0) { part2++; }
			currentPosition += 100;				//our position is always between 0 and 99;
		}
		if (currentPosition == 0) { part1++; part2++; }
	}

	std::cout << "Part 1 result is: " << part1 << "\n";
	std::cout << "Part 2 result is: " << part2;
}

//6394 (high?)