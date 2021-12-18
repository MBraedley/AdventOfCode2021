// Day18.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "SnailNumber.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

int main()
{
	std::filesystem::path input("input.txt");

	std::ifstream inStrm;
	inStrm.open(input);

	std::vector<std::string> values;
	std::string val;
	while (inStrm >> val)
	{
		values.emplace_back(val);
	}

	SnailNumber sum(values[0]);

	for (std::size_t i = 1; i < values.size(); i++)
	{
		sum = sum + SnailNumber(values[i]);
	}

	std::cout << "Part 1: " << sum.GetMagnitude() << std::endl;

	std::uint64_t maxMag = 0;

	for (std::size_t i = 0; i < values.size(); i++)
	{
		for (std::size_t j = 0; j < values.size(); j++)
		{
			if (i != j)
			{
				auto num = SnailNumber(values[i]) + SnailNumber(values[j]);
				maxMag = std::max(maxMag, num.GetMagnitude());
			}
		}
	}

	std::cout << "Part 2: " << maxMag << std::endl;
}
