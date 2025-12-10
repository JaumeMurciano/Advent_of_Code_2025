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

//structure used to store each Box
struct Point
{
	int64_t x{-1};
	int64_t y{-1};
	int64_t z{-1};
	bool operator<(const Point& otherPoint) const { return x < otherPoint.x || x == otherPoint.x && y < otherPoint.y || x == otherPoint.x && y == otherPoint.y && z < otherPoint.z; }
};

//structure used to store the pairs
struct Pair
{
	double distance{};
	std::array<Point, 2> connection{};
	bool operator<(const Pair& otherPair) const { return distance < otherPair.distance; }
};

//function used to calculate the part 1 result after n iterations
int64_t calculatePart1Result(std::vector<std::set<Point>>& allCircuits)
{
	std::array<int64_t, 3> part1Result{};
	for (std::set<Point>& eachCircuit : allCircuits)
	{
		if (eachCircuit.size() >= part1Result[0])
		{
			part1Result[2] = part1Result[1];
			part1Result[1] = part1Result[0];
			part1Result[0] = eachCircuit.size();
		}
		else if (eachCircuit.size() >= part1Result[1])
		{
			part1Result[2] = part1Result[1];
			part1Result[1] = eachCircuit.size();
		}
		else if (eachCircuit.size() > part1Result[2])
		{
			part1Result[2] = eachCircuit.size();
		}
	}
	return part1Result[0] * part1Result[1] * part1Result[2];
}

int main()
{
	std::ifstream myReadFile("day08_input.txt");
	std::string inputLine{};

	int64_t part1{};
	int64_t part2{};

	int32_t nConnections{1000};
	std::vector<Pair> shortestPairs{};
	std::vector<Point> allBoxes{};

	//first, store all boxes
	while (std::getline(myReadFile, inputLine))
	{
		std::stringstream eachLine{inputLine};
		std::string eachNum{};
		Point newBox{};
		while (std::getline(eachLine, eachNum, ','))
		{
			if (newBox.x == -1) { newBox.x = std::stoll(eachNum); }
			else if (newBox.y == -1) { newBox.y = std::stoll(eachNum); }
			else if (newBox.z == -1) { newBox.z = std::stoll(eachNum); }
		}
		allBoxes.emplace_back(newBox);
	}
	//then calculate all pairs
	for (int32_t i{}; i < allBoxes.size(); i++)
	{
		for (int32_t j{ i + 1 }; j < allBoxes.size(); j++)
		{
			Pair newPair{};
			newPair.connection = std::array<Point, 2>{allBoxes[i], allBoxes[j]};
			newPair.distance = sqrt(pow(allBoxes[i].x - allBoxes[j].x, 2) + pow(allBoxes[i].y - allBoxes[j].y, 2) + pow(allBoxes[i].z - allBoxes[j].z, 2));
			shortestPairs.emplace_back(newPair);
		}
	}
	std::sort(shortestPairs.begin(), shortestPairs.end()); //order the pairs by distance (see operator< at "Pair")
	std::vector<std::set<Point>> allCircuits{};

	//now connect the first nPairs
	for (int32_t i{}; i < shortestPairs.size(); i++)
	{
		if (i == nConnections) { part1 = calculatePart1Result(allCircuits); } //after 1000 connections calculate part 1 result
		std::array<int32_t, 2> pairsInCircuits{ -1,-1 };
		for (int32_t j{}; j < allCircuits.size(); j++)	//see if the boxes are inside any circuit
		{
			if (allCircuits[j].find(shortestPairs[i].connection[0]) != allCircuits[j].end()) { pairsInCircuits[0] = j; }
			if (allCircuits[j].find(shortestPairs[i].connection[1]) != allCircuits[j].end()) { pairsInCircuits[1] = j; }
		}
		if (pairsInCircuits[0] == -1 && pairsInCircuits[1] == -1)  //if both boxes are outside, create a new circuit for them
		{
			std::set<Point> newSet{};
			newSet.emplace(shortestPairs[i].connection[0]);
			newSet.emplace(shortestPairs[i].connection[1]);
			allCircuits.emplace_back(newSet);
		}
		else if (pairsInCircuits[0] == -1 && pairsInCircuits[1] != -1) //if one box is inside a circuit, add the other one to it
		{
			allCircuits[pairsInCircuits[1]].emplace(shortestPairs[i].connection[0]);
		}
		else if (pairsInCircuits[0] != -1 && pairsInCircuits[1] == -1) //if one box is inside a circuit, add the other one to it
		{
			allCircuits[pairsInCircuits[0]].emplace(shortestPairs[i].connection[1]);
		}
		else if (pairsInCircuits[0] != pairsInCircuits[1]) //if both boxes are inside a circuit but it is a different circuit, merge both circuits
		{
			for (Point eachPoint : allCircuits[pairsInCircuits[1]])
			{
				allCircuits[pairsInCircuits[0]].emplace(eachPoint);
			}
			allCircuits.erase(allCircuits.begin() + pairsInCircuits[1]);
		}
		if (allCircuits.size() == 1 && allCircuits[0].size() == allBoxes.size() && part2 == 0)	//if all boxes are connected in a circuit, calculate part 2 and stop
		{
			part2 = shortestPairs[i].connection[0].x * shortestPairs[i].connection[1].x;
			break;
		}
	}
	std::cout << "Part 1 result is: " << part1 << "\n";
	std::cout << "Part 2 result is: " << part2;
}
