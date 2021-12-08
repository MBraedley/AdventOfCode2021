// Day01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <map>

std::uint64_t TriangularNumber(std::uint32_t n)
{
	return (n * (static_cast<std::uint64_t>(n) + 1)) / 2;
}

int main()
{
	std::filesystem::path input("input.txt");

	std::ifstream inStrm;
	inStrm.open(input);

	std::vector<std::int32_t> crabs;
	char c;
	do
	{
		std::int32_t val;
		inStrm >> val;
		crabs.push_back(val);
	} while (inStrm >> c);

	auto minVal = *std::min_element(crabs.begin(), crabs.end());
	auto maxVal = *std::max_element(crabs.begin(), crabs.end());

	std::uint32_t minOffset = std::numeric_limits<std::uint32_t>::max();

	for (std::int32_t i = minVal; i <= maxVal; i++)
	{
		std::uint32_t offset = 0;
		for (auto val : crabs)
		{
			offset += std::abs(i - val);
		}

		if (offset < minOffset)
		{
			minOffset = offset;
		}
	}

	std::cout << "Part 1: " << minOffset << std::endl;

	minOffset = std::numeric_limits<std::uint32_t>::max();

	for (std::int32_t i = minVal; i <= maxVal; i++)
	{
		std::uint32_t offset = 0;
		for (auto val : crabs)
		{
			offset += TriangularNumber( std::abs(i - val) );
		}

		if (offset < minOffset)
		{
			minOffset = offset;
		}
	}

	std::cout << "Part 2: " << minOffset << std::endl;
}
