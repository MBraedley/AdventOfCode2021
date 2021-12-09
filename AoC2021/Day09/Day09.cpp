// Day09.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <map>
#include <set>

int main()
{
	std::filesystem::path input("input.txt");

	std::ifstream inStrm;
	inStrm.open(input);

	std::vector<std::string> values;
	std::string val;
	while (inStrm >> val)
	{
		values.push_back(val);
	}

	std::map<std::pair<std::size_t, std::size_t>, int> lowPoints;

	std::size_t maxX = values[0].size() - 1;
	std::size_t maxY = values.size() - 1;
	int count = 0;

	for (std::size_t y = 0; y <= maxY; y++)
	{
		for (std::size_t x = 0; x <= maxX; x++)
		{
			auto testVal = values[y][x];
			if (
				(x == 0 || testVal < values[y][x - 1]) &&
				(x == maxX || testVal < values[y][x + 1]) &&
				(y == 0 || testVal < values[y - 1][x]) &&
				(y == maxY || testVal < values[y + 1][x]))
			{
				lowPoints.emplace(std::make_pair(x, y), static_cast<int>(testVal - '0'));
				count += static_cast<int>(testVal - '0') + 1;
			}
		}
	}

	std::cout << "Part 1: " << count << std::endl;

	std::map<std::pair<std::size_t, std::size_t>, std::set<std::pair<std::size_t, std::size_t>>> basins;

	for (auto& [startPoint, level] : lowPoints)
	{
		std::set<std::pair<std::size_t, std::size_t>> basin;
		std::set<std::pair<std::size_t, std::size_t>> edgePoints;
		std::set<std::pair<std::size_t, std::size_t>> pointsToCheck;
		basin.insert(startPoint);
		auto addPointsToCheck = [&](std::size_t x, std::size_t y)
		{
			if (x != 0 && !basin.contains({ x - 1, y }) && !edgePoints.contains({ x - 1, y }))
			{
				pointsToCheck.emplace(x - 1, y);
			}

			if (x != maxX && !basin.contains({ x + 1, y }) && !edgePoints.contains({ x + 1, y }))
			{
				pointsToCheck.emplace(x + 1, y);
			}

			if (y != 0 && !basin.contains({ x, y - 1 }) && !edgePoints.contains({ x, y - 1 }))
			{
				pointsToCheck.emplace(x, y - 1);
			}

			if (y != maxY && !basin.contains({ x, y + 1 }) && !edgePoints.contains({ x, y + 1 }))
			{
				pointsToCheck.emplace(x, y + 1);
			}
		};
		
		addPointsToCheck(startPoint.first, startPoint.second);

		while (!pointsToCheck.empty())
		{
			auto next = pointsToCheck.begin();
			if (values[next->second][next->first] == '9')
			{
				edgePoints.emplace(*next);
			}
			else
			{
				basin.emplace(*next);
				addPointsToCheck(next->first, next->second);
			}
			pointsToCheck.erase(next);
		}

		basins.emplace(startPoint, basin);
	}

	std::vector<std::size_t> basinSizes;
	for (auto& [startingPoint, basinPoints] : basins)
	{
		basinSizes.push_back(basinPoints.size());
	}

	std::sort(basinSizes.begin(), basinSizes.end(), std::cmp_greater<std::size_t, std::size_t>);

	auto output = basinSizes[0] * basinSizes[1] * basinSizes[2];

	std::cout << "Part 2: " << output << std::endl;
}
