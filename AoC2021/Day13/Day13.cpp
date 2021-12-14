// Day13.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include <set>
#include <regex>
#include <cassert>

using TransparencySheet = std::set<std::pair<std::int32_t, std::int32_t>>;

void FoldX(TransparencySheet& sheet, std::int32_t x)
{
	TransparencySheet nextSheet;
	for (auto& coord : sheet)
	{
		if (coord.first > x)
		{
			nextSheet.emplace(2 * x - coord.first, coord.second);
		}
		else
		{
			nextSheet.emplace(coord);
		}
	}
	std::swap(sheet, nextSheet);
}

void FoldY(TransparencySheet& sheet, std::int32_t y)
{
	TransparencySheet nextSheet;
	for (auto& coord : sheet)
	{
		if (coord.second > y)
		{
			nextSheet.emplace(coord.first, 2 * y - coord.second);
		}
		else
		{
			nextSheet.emplace(coord);
		}
	}
	std::swap(sheet, nextSheet);
}

int main()
{
	std::filesystem::path input("input.txt");

	std::ifstream inStrm;
	inStrm.open(input);

	TransparencySheet sheet;
	std::string line;

	std::regex coords("([0-9]+),([0-9]+)");
	std::smatch m;

	while (std::getline(inStrm, line))
	{
		if (!std::regex_match(line, m, coords))
		{
			break;	//Just read the empty line
		}
		std::int32_t x = std::stoi(m[1]);
		std::int32_t y = std::stoi(m[2]);
		sheet.emplace(x, y);
	}

	std::regex foldInstruction("(x|y)=([0-9]+)");
	while (std::getline(inStrm, line))
	{
		bool matched = std::regex_search(line, m, foldInstruction);
		assert(matched);
		if (m[1] == "x")
		{
			FoldX(sheet, std::stoi(m[2]));
		}
		else
		{
			FoldY(sheet, std::stoi(m[2]));
		}

		std::cout << "Part 1: " << sheet.size() << std::endl;
	}

	std::size_t maxX = 0;
	std::size_t maxY = 0;

	for (auto& [x, y] : sheet)
	{
		assert(x >= 0);
		assert(y >= 0);
		if (x > maxX)
		{
			maxX = x;
		}

		if (y > maxY)
		{
			maxY = y;
		}
	}

	std::vector<std::vector<std::string>> foldedSheet(maxY + 1, std::vector<std::string>(maxX + 1, " "));

	for (auto& [x, y] : sheet)
	{
		foldedSheet[y][x] = "#";
	}

	for (auto& row : foldedSheet)
	{
		for (std::string& col : row)
		{
			std::cout << col;
		}
		std::cout << std::endl;
	}
	//std::cout << "Part 2: " << count << std::endl;
}
