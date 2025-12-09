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
//coordinate strut
struct Point
{
	int32_t row{};
	int32_t col{};
	bool operator>(const Point& otherPoint) const { return row > otherPoint.row || row == otherPoint.row && col > otherPoint.col; } //used in the Priority queue
	bool operator<(const Point& otherPoint) const { return row < otherPoint.row || row == otherPoint.row && col < otherPoint.col; } //used to for std::map<Point,int64_t>
};

int main()
{
	std::ifstream myReadFile("day07_input.txt");
	std::string inputLine{};
	
	int64_t part2{0};

	std::vector<std::string> inputMap{};
	Point startingPoint{1,0};
	std::map<Point, int64_t> lineLifetimes{};	//dynamic programming map to store the number of lifetimes
	
	while (std::getline(myReadFile, inputLine))	//read the input
	{
		inputMap.emplace_back(inputLine);
		if (inputMap.size() == 1) { startingPoint.col = inputLine.find('S'); };
	}

	std::priority_queue<Point, std::vector<Point>, std::greater<Point>> splitsLeft{};	//the queue is a priority queue in order to clear the splits in order
	std::set<Point> allSplits{};				//set used to count the splits that are used
	
	splitsLeft.emplace(startingPoint);			//start the simulation
	lineLifetimes[startingPoint]++;

	while (splitsLeft.size() > 0)
	{
		Point currentPosition = splitsLeft.top();	//pop the first element
		splitsLeft.pop();
		Point startingReference{currentPosition};	//store the branch origin
		while (true)
		{
			if (currentPosition.col < 0 || currentPosition.col >= inputMap[0].size() || currentPosition.row >= inputMap.size()) { part2 += lineLifetimes[startingReference]; break; } //if invalid position, the simulation ends and add lifetimes to part 2
			if (inputMap[currentPosition.row][currentPosition.col] == '^')
			{
				if (lineLifetimes[Point{ currentPosition.row,currentPosition.col - 1 }] == 0) { splitsLeft.emplace(Point{ currentPosition.row,currentPosition.col - 1 }); }	//if branch has not been emplaced, emplace it
				if (lineLifetimes[Point{ currentPosition.row,currentPosition.col + 1 }] == 0) { splitsLeft.emplace(Point{ currentPosition.row,currentPosition.col + 1 }); }
				lineLifetimes[Point{ currentPosition.row,currentPosition.col - 1 }] += lineLifetimes[startingReference];	//add the number of lifetimes of the new branch
				lineLifetimes[Point{ currentPosition.row,currentPosition.col + 1 }] += lineLifetimes[startingReference];
				allSplits.emplace(currentPosition);	//add the split position for part 1
				break;
			}
			else if (inputMap[currentPosition.row][currentPosition.col] == '.')
			{
				currentPosition.row++;				//continue the simulation until the end or a split is reached
			}
			else { break; }
		}
	}

	std::cout << "Part 1 result is: " << allSplits.size() << "\n";
	std::cout << "Part 2 result is: " << part2;
}