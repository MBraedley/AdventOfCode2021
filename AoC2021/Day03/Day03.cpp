// Day03.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <bitset>
#include <cassert>

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

	std::vector<std::pair<std::uint32_t, std::uint32_t>> counts(values[0].size(), { 0, 0 });

	for (auto item : values)
	{
		for (std::size_t i = 0; i < item.size(); i++)
		{
			if (item[i] == '0')
			{
				counts[i].first++;
			}
			else
			{
				counts[i].second++;
			}
		}
	}

	std::uint32_t gamma = 0;
	std::uint32_t epsilon = 0;

	for (auto [count0, count1] : counts)
	{
		gamma *= 2;
		epsilon *= 2;

		if (count0 > count1)
		{
			epsilon++;
		}
		else
		{
			gamma++;
		}
	}

	std::cout << "Part 1: " << gamma << " * " << epsilon << " = " << gamma * epsilon << std::endl;

	std::vector<std::string> o2( values.begin(), values.end() );

	for (std::size_t i = 0; i < values[0].size(); i++)
	{
		std::vector<std::string> o2_0;
		std::vector<std::string> o2_1;
		for (auto item : o2)
		{
			if (item[i] == '0')
			{
				o2_0.push_back(item);
			}
			else
			{
				o2_1.push_back(item);
			}
		}

		if (o2_1.size() >= o2_0.size())
		{
			std::swap(o2, o2_1);
		}
		else
		{
			std::swap(o2, o2_0);
		}

		if (o2.size() == 1)
		{
			break;
		}
	}

	assert(o2.size() == 1);

	auto o2Val = std::bitset<32>(o2[0]).to_ulong();

	std::vector<std::string> co2(values.begin(), values.end());

	for (std::size_t i = 0; i < values[0].size(); i++)
	{
		std::vector<std::string> co2_0;
		std::vector<std::string> co2_1;
		for (auto item : co2)
		{
			if (item[i] == '0')
			{
				co2_0.push_back(item);
			}
			else
			{
				co2_1.push_back(item);
			}
		}

		if (co2_0.size() <= co2_1.size())
		{
			std::swap(co2, co2_0);
		}
		else
		{
			std::swap(co2, co2_1);
		}

		if (co2.size() == 1)
		{
			break;
		}
	}

	assert(co2.size() == 1);

	auto co2Val = std::bitset<32>(co2[0]).to_ulong();

	std::cout << "Part 2: " << o2Val << " * " << co2Val << " = " << o2Val * co2Val << std::endl;
}
