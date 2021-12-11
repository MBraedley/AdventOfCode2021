// Day11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Octopus.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

int main()
{
	std::filesystem::path input("input.txt");

	std::ifstream inStrm;
	inStrm.open(input);

	std::vector<std::vector<std::shared_ptr<Octopus>>> grid;
	for (std::size_t row = 0; row < 10; row++)
	{
		std::vector<std::shared_ptr<Octopus>> gridRow;
		for (std::size_t col = 0; col < 10; col++)
		{
			char c;
			inStrm >> c;
			std::shared_ptr<Octopus> octopus = std::make_shared<Octopus>(c - '0');
			gridRow.push_back(octopus);

			if (row != 0)
			{
				if (col != 0)
				{
					octopus->AddNeighbour(grid[row - 1][col - 1]);
				}
				octopus->AddNeighbour(grid[row - 1][col]);
				if (col + 1 < grid[row - 1].size())
				{
					octopus->AddNeighbour(grid[row - 1][col + 1]);
				}
			}

			if (col != 0)
			{
				octopus->AddNeighbour(gridRow[col - 1]);
			}
		}
		grid.push_back(gridRow);
	}

	std::uint32_t count = 0;
	for (std::uint32_t i = 0; i < 100; i++)
	{
		//Step each octopus
		for (auto& row : grid)
		{
			for (auto& octopus : row)
			{
				octopus->Step();
			}
		}

		//Count the flashes
		for (auto& row : grid)
		{
			for (auto& octopus : row)
			{
				if (octopus->Flashed())
				{
					count++;
				}
			}
		}
	}

	std::cout << "Part 1: " << count << std::endl;

	std::uint32_t step = 100;
	do
	{
		count = 0;
		step++;

		//Step each octopus
		for (auto& row : grid)
		{
			for (auto& octopus : row)
			{
				octopus->Step();
			}
		}

		//Count the flashes
		for (auto& row : grid)
		{
			for (auto& octopus : row)
			{
				if (octopus->Flashed())
				{
					count++;
				}
			}
		}
	} while (count != 100);
	
	std::cout << "Part 2: " << step << std::endl;
}
