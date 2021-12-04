// Day02.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <cassert>

int main()
{
	std::filesystem::path input("input.txt");

	std::ifstream inStrm;
	inStrm.open(input);

	std::string direction;
	std::uint32_t distance;

	std::uint32_t x = 0;
	std::uint32_t y = 0;

	std::vector<std::tuple<std::string, std::uint32_t>> values;

	while (inStrm >> direction >> distance)
	{
		values.emplace_back(direction, distance);
		if (direction == "forward")
		{
			x += distance;
		}
		else if (direction == "up")
		{
			y -= distance;
		}
		else if (direction == "down")
		{
			y += distance;
		}
		else
		{
			assert(false);
		}
	}

	std::cout << "Part 1: " << x << "*" << y << "=" << x * y << std::endl;

	x = 0;
	y = 0;
	std::int32_t aim = 0;

	for (auto& [dir, dist] : values)
	{
		if (dir == "forward")
		{
			x += dist;
			y += dist * aim;
		}
		else if (dir == "up")
		{
			aim -= dist;
		}
		else if (dir == "down")
		{
			aim += dist;
		}
		else
		{
			assert(false);
		}
	}

	std::cout << "Part 2: " << x << "*" << y << "=" << x * y << std::endl;
}