// Day01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

int main()
{
	std::filesystem::path input("input.txt");

	std::ifstream inStrm;
	inStrm.open(input);

	std::vector<std::uint32_t> values;
	std::uint32_t val;
	while (inStrm >> val)
	{
		values.push_back(val);
	}

	std::uint32_t count = 0;
	for (std::uint32_t i = 1; i < values.size(); i++)
	{
		if (values[i - 1] < values[i])
		{
			count++;
		}
	}

	std::cout << "Part 1: " << count << std::endl;

	std::vector<std::uint32_t> rollAvg;
	for (std::uint32_t i = 1; i < values.size() - 1; i++)
	{
		rollAvg.push_back(values[i - 1] + values[i] + values[i + 1]);
	}

	count = 0;
	for (std::uint32_t i = 1; i < rollAvg.size(); i++)
	{
		if (rollAvg[i - 1] < rollAvg[i])
		{
			count++;
		}
	}

	std::cout << "Part 2: " << count << std::endl;
}
