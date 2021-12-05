// Day05.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <map>

int main()
{
	std::filesystem::path input("input.txt");

	std::ifstream inStrm;
	inStrm.open(input);

	std::vector<std::string> values;
	std::string val;
	while (std::getline(inStrm, val))
	{
		values.push_back(val);
	}

	int startX, startY, endX, endY;
	std::map<std::pair<int, int>, std::uint32_t> oceanFloor;

	for (auto& line : values)
	{
		std::stringstream sstrm(line);
		char c;
		std::string str;
		sstrm >> startX >> c >> startY >> str >> endX >> c >> endY;

		if (startX == endX)
		{
			auto x = startX;
			for (int y = std::min(startY, endY); y <= std::max(startY, endY); y++)
			{
				oceanFloor[{x, y}]++;
			}
		}

		if (startY == endY)
		{
			auto y = startY;
			for (int x = std::min(startX, endX); x <= std::max(startX, endX); x++)
			{
				oceanFloor[{x, y}]++;
			}
		}
	}

	auto count = std::count_if(oceanFloor.begin(), oceanFloor.end(), [](const auto& val) { return val.second >= 2; });

	std::cout << "Part 1: " << count << std::endl;

	for (auto& line : values)
	{
		std::stringstream sstrm(line);
		char c;
		std::string str;
		sstrm >> startX >> c >> startY >> str >> endX >> c >> endY;

		if (std::abs(startX - endX) == std::abs(startY - endY))
		{
			int xInc = startX < endX ? 1 : -1;
			int yInc = startY < endY ? 1 : -1;

			for (auto x = startX, y = startY; x != endX && y != endY; x += xInc, y += yInc)
			{
				oceanFloor[{x, y}]++;
			}

			oceanFloor[{endX, endY}]++;
		}
	}

	count = std::count_if(oceanFloor.begin(), oceanFloor.end(), [](const auto& val) { return val.second >= 2; });

	std::cout << "Part 2: " << count << std::endl;
}
