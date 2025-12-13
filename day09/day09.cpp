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
//coordinate struct
struct Point
{
	int64_t x{};
	int64_t y{};
};

//ray-cast pont in Polygon. Note! Due to my input, I can skip this part, but as not all inputs are like mine, skip this.
bool pointInPolygon(Point& pointToCheck, std::vector<Point>& allPoints)
{
	int32_t nCrossings{};
	if (pointToCheck.x == 7 && pointToCheck.y == 7)
	{
		int a = 0;
	}
	for (int32_t i{}; i < allPoints.size(); i++)
	{
		Point segmentStart = allPoints[i];
		Point segmentEnd = allPoints[(i+1)%allPoints.size()];
		if (segmentStart.y == segmentEnd.y && segmentStart.y == pointToCheck.y && ((segmentStart.x < pointToCheck.x && pointToCheck.x < segmentEnd.x) || (segmentStart.x > pointToCheck.x && pointToCheck.x > segmentEnd.x))) 
		{
			return true; //point is in a horizontal segment
		}
		if (segmentStart.x == segmentEnd.x && segmentStart.x == pointToCheck.x && ((segmentStart.y < pointToCheck.y && pointToCheck.y < segmentEnd.y) || (segmentStart.y > pointToCheck.y && pointToCheck.y > segmentEnd.y)))
		{
			return true; //point is in a vertical segment
		}
		if(segmentStart.y == segmentEnd.y) {continue;} //line is horizontal, skip it
		if ((segmentStart.y > pointToCheck.y && segmentEnd.y > pointToCheck.y) || (segmentStart.y < pointToCheck.y && segmentEnd.y < pointToCheck.y)) { continue; } //line is vertical, but we do not cross it
		if ((segmentStart.y < pointToCheck.y && pointToCheck.y < segmentEnd.y) || (segmentStart.y > pointToCheck.y && pointToCheck.y > segmentEnd.y))				//there is one corssing
		{
			if (segmentStart.x > pointToCheck.x) { nCrossings++; }
		}
		if (pointToCheck.x == segmentStart.x) { continue; } //this case is already checked when x == segment end
		if (pointToCheck.x == segmentEnd.x)					//check if the next border goes to the same direction as the current border. If it does, add one crossing
		{
			int32_t iNext = (i + 2) % allPoints.size();
			int32_t jNext = (i + 3) % allPoints.size();
			int32_t currYMovenemnt = segmentEnd.y - segmentStart.y;
			int32_t nextYMovement = allPoints[jNext].y - allPoints[iNext].y;
			if ((currYMovenemnt > 0 && nextYMovement > 0) || (currYMovenemnt < 0 && nextYMovement < 0)) 
			{
				nCrossings++;
			}
		}
	}
	return nCrossings % 2 == 1;
}

//function that checks if any border crosses or is inside the polygon
bool checkPerimeterCrossings(Point& corner1, Point& corner2, std::vector<Point>& allPoints)
{
	int32_t lowerBorder = corner1.y < corner2.y ? corner1.y : corner2.y;
	int32_t higherBorder = corner1.y > corner2.y ? corner1.y : corner2.y;
	int32_t leftBorder = corner1.x < corner2.x ? corner1.x : corner2.x;
	int32_t rightBorder = corner1.x > corner2.x ? corner1.x : corner2.x;
	for (int32_t i{}; i < allPoints.size(); i++)
	{
		Point segmentStart = allPoints[i];
		Point segmentEnd = allPoints[(i + 1) % allPoints.size()];
		if (segmentStart.x == segmentEnd.x && leftBorder < segmentStart.x && segmentStart.x < rightBorder) //line is vertical and in bounds
		{
			int32_t lowerPoint = segmentStart.y < segmentEnd.y ? segmentStart.y : segmentEnd.y;
			int32_t higherPoint = segmentStart.y > segmentEnd.y ? segmentStart.y : segmentEnd.y;
			if (higherPoint <= lowerBorder) { continue; }	//current perimeter segment is at a lower position than the polygon
			if (lowerPoint >= higherBorder) { continue; }	//current perimeter segment is at a gigher position than the polygon
			return true; //vertical segment crosses the polygon
		}
		else if (segmentStart.y == segmentEnd.y && lowerBorder < segmentStart.y && segmentStart.y < higherBorder) //line is horizontal and in bounds
		{
			int32_t leftPoint = segmentStart.x < segmentEnd.x ? segmentStart.x : segmentEnd.x;
			int32_t rightPoint = segmentStart.x > segmentEnd.x ? segmentStart.x : segmentEnd.x;
			if (rightPoint <= leftBorder) { continue; }		//current perimeter segment is at the left of the polygon
			if (leftPoint >= rightBorder) { continue; }		//current perimeter segment is at the right of the polyogon
			return true; //horizontal segment crosses the polygon
		}
	}
	return false;
}

int main()
{
	std::ifstream myReadFile("day09_input.txt");
	std::string inputLine{};

	int64_t part1{};
	int64_t part2{};
	std::vector<Point> allTiles{};	//vector that stores all the perimeters of the polygon

	while (std::getline(myReadFile, inputLine))	//store all segments
	{
		std::stringstream eachLine{inputLine};
		std::string eachNum{};
		Point newTile{};
		getline(eachLine, eachNum, ',');
		newTile.x = std::stoll(eachNum);
		getline(eachLine, eachNum, ',');
		newTile.y = std::stoll(eachNum);
		allTiles.emplace_back(newTile);
	}
	for (int32_t i{}; i < allTiles.size(); i++)
	{
		for (int32_t j{i+1}; j < allTiles.size(); j++)
		{
			//part 1: calculate and store the largest area.
			int64_t rectangleArea = (abs(allTiles[i].x-allTiles[j].x)+1) * (abs(allTiles[i].y - allTiles[j].y) + 1);
			if (rectangleArea > part1) { part1 = rectangleArea; }

			//part 2: check if any part of the perimeter crosses the polygon and if it doesn't check that any point inside the rectangle is inside the polygon
			Point middlePoint{ allTiles[i].x + (allTiles[j].x - allTiles[i].x) / 2,allTiles[i].y + (allTiles[j].y - allTiles[i].y) / 2 };
			if (allTiles[i].x == allTiles[j].x || allTiles[i].y == allTiles[j].y) { continue; }
			if (!checkPerimeterCrossings(allTiles[i],allTiles[j], allTiles) && pointInPolygon(middlePoint, allTiles))
			{
				if (rectangleArea > part2) { 
					part2 = rectangleArea; 
				}
			}
		}
	}

	std::cout << "Part 1 result is: " << part1 << "\n";
	std::cout << "Part 2 result is: " << part2;
}