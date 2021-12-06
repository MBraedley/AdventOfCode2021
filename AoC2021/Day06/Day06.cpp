// Day06.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <map>

int main()
{
	std::filesystem::path input("input.txt");

	std::ifstream inStrm;
	inStrm.open(input);

	std::map<std::uint32_t, std::uint64_t> fish;
	char c;
	do
	{
		std::uint32_t val;
		inStrm >> val;
		fish[val]++;
	} while (inStrm >> c);


	for (std::uint32_t i = 0; i < 256; i++)
	{
		if (i==80)
		{
			std::uint64_t count = 0;
			for (auto [age, num] : fish)
			{
				count += num;
			}

			std::cout << "Part 1: " << count << std::endl;
		}

		std::map<std::uint32_t, std::uint64_t> nextGen;

		for (auto [age, num] : fish)
		{
			if (age == 0)
			{
				nextGen[6] += num;
				nextGen[8] += num;
			}
			else
			{
				nextGen[age - 1] += num;
			}
		}
		
		std::swap(fish, nextGen);
	}

	std::uint64_t count = 0;
	for (auto [age, num] : fish)
	{
		count += num;
	}

	std::cout << "Part 2: " << count << std::endl;
}
