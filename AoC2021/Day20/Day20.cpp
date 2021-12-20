// Day20.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <bitset>
#include <set>
#include <cassert>

void PrintImage(const std::set<std::pair<int, int>>& image)
{
	int minX = std::numeric_limits<int>::max();
	int minY = std::numeric_limits<int>::max();
	int maxX = std::numeric_limits<int>::min();
	int maxY = std::numeric_limits<int>::min();

	for (const auto& pos : image)
	{
		minX = std::min(minX, pos.first);
		maxX = std::max(maxX, pos.first);
		minY = std::min(minY, pos.second);
		maxY = std::max(maxY, pos.second);
	}

	std::vector<std::vector<bool>> printable(maxY - minY + 1, std::vector<bool>(maxX - minX + 1, false));

	for (const auto& pos : image)
	{
		printable[pos.second - minY][pos.first - minX] = true;
	}

	for (const auto& row : printable)
	{
		for (const auto& col : row)
		{
			std::cout << (col ? "#" : " ");
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int main()
{
	std::filesystem::path input("input.txt");

	std::ifstream inStrm;
	inStrm.open(input);

	std::string line;
	std::getline(inStrm, line);
	assert(line.size() == 512);
	
	line.assign(line.rbegin(), line.rend());
	std::bitset<512> enhanceLookup(line, 0, line.size(), '.', '#');

	std::getline(inStrm, line);	//empty line

	int y = 0;
	std::set<std::pair<int, int>> image;
	while (std::getline(inStrm, line))
	{
		for (int x = 0; x < line.size(); x++)
		{
			//only insert on pixels, will speed up processing
			if (line[x] == '#')
			{
				image.insert({ x, y });
			}
		}
		y++;
	}

	PrintImage(image);

	std::bitset<9> convolve;

	if (!enhanceLookup[0])	//the algorithm plays nicely with a blank field
	{
		for (std::size_t i = 0; i < 2; i++)
		{
			std::set<std::pair<int, int>> imageNext;
			//2 step process: generate list of points to check, then check them
			std::set<std::pair<int, int>> points;
			for (auto& pos : image)
			{
				points.insert({ pos.first - 1, pos.second - 1 });
				points.insert({ pos.first, pos.second - 1 });
				points.insert({ pos.first + 1, pos.second - 1 });
				points.insert({ pos.first - 1, pos.second });
				points.insert(pos);
				points.insert({ pos.first + 1, pos.second });
				points.insert({ pos.first - 1, pos.second + 1 });
				points.insert({ pos.first, pos.second + 1 });
				points.insert({ pos.first + 1, pos.second + 1 });
			}

			for (auto& pos : points)
			{
				convolve.reset();
				convolve[0] = image.contains({ pos.first + 1, pos.second + 1 });
				convolve[1] = image.contains({ pos.first, pos.second + 1 });
				convolve[2] = image.contains({ pos.first - 1, pos.second + 1 });
				convolve[3] = image.contains({ pos.first + 1, pos.second });
				convolve[4] = image.contains({ pos.first, pos.second });
				convolve[5] = image.contains({ pos.first - 1, pos.second });
				convolve[6] = image.contains({ pos.first + 1, pos.second - 1 });
				convolve[7] = image.contains({ pos.first, pos.second - 1 });
				convolve[8] = image.contains({ pos.first - 1, pos.second - 1 });

				if (enhanceLookup[convolve.to_ulong()])
				{
					imageNext.insert(pos);
				}
			}

			std::swap(image, imageNext);
			PrintImage(image);
		}
	}
	else	//we need to store the negative every other iteration
	{
		for (int i = 0; i < 25; i++)
		{
			assert(!enhanceLookup[511]);
			std::set<std::pair<int, int>> imageNext;
			//2 step process: generate list of points to check, then check them
			std::set<std::pair<int, int>> points;
			for (auto& pos : image)
			{
				points.insert({ pos.first - 1, pos.second - 1 });
				points.insert({ pos.first, pos.second - 1 });
				points.insert({ pos.first + 1, pos.second - 1 });
				points.insert({ pos.first - 1, pos.second });
				points.insert(pos);
				points.insert({ pos.first + 1, pos.second });
				points.insert({ pos.first - 1, pos.second + 1 });
				points.insert({ pos.first, pos.second + 1 });
				points.insert({ pos.first + 1, pos.second + 1 });
			}

			for (auto& pos : points)
			{
				convolve.reset();
				convolve[0] = image.contains({ pos.first + 1, pos.second + 1 });
				convolve[1] = image.contains({ pos.first, pos.second + 1 });
				convolve[2] = image.contains({ pos.first - 1, pos.second + 1 });
				convolve[3] = image.contains({ pos.first + 1, pos.second });
				convolve[4] = image.contains({ pos.first, pos.second });
				convolve[5] = image.contains({ pos.first - 1, pos.second });
				convolve[6] = image.contains({ pos.first + 1, pos.second - 1 });
				convolve[7] = image.contains({ pos.first, pos.second - 1 });
				convolve[8] = image.contains({ pos.first - 1, pos.second - 1 });

				if (!enhanceLookup[convolve.to_ulong()])
				{
					imageNext.insert(pos);
				}
			}

			std::swap(image, imageNext);

			//Iteration 2
			points.clear();
			imageNext.clear();
			for (auto& pos : image)
			{
				points.insert({ pos.first - 1, pos.second - 1 });
				points.insert({ pos.first, pos.second - 1 });
				points.insert({ pos.first + 1, pos.second - 1 });
				points.insert({ pos.first - 1, pos.second });
				points.insert(pos);
				points.insert({ pos.first + 1, pos.second });
				points.insert({ pos.first - 1, pos.second + 1 });
				points.insert({ pos.first, pos.second + 1 });
				points.insert({ pos.first + 1, pos.second + 1 });
			}

			for (auto& pos : points)
			{
				convolve.reset();
				convolve[0] = image.contains({ pos.first + 1, pos.second + 1 });
				convolve[1] = image.contains({ pos.first, pos.second + 1 });
				convolve[2] = image.contains({ pos.first - 1, pos.second + 1 });
				convolve[3] = image.contains({ pos.first + 1, pos.second });
				convolve[4] = image.contains({ pos.first, pos.second });
				convolve[5] = image.contains({ pos.first - 1, pos.second });
				convolve[6] = image.contains({ pos.first + 1, pos.second - 1 });
				convolve[7] = image.contains({ pos.first, pos.second - 1 });
				convolve[8] = image.contains({ pos.first - 1, pos.second - 1 });

				convolve.flip();

				if (enhanceLookup[convolve.to_ulong()])
				{
					imageNext.insert(pos);
				}
			}

			std::swap(image, imageNext);
			if ( i == 0)
			{
				std::cout << "Part 1: " << image.size() << std::endl;
			}
		}
	}

	std::cout << "Part 2: " << image.size() << std::endl;
}
