// Day20.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <bitset>
#include <map>
#include <cassert>

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
	std::map<std::pair<int, int>, bool> image;
	while (std::getline(inStrm, line))
	{
		for (int x = 0; x < line.size(); x++)
		{
			//only insert on pixels, will speed up processing
			if (line[x] == '#')
			{
				image[{x, y}] = true;
			}
		}
	}

	std::bitset<9> convolve;
	for (std::size_t i = 0; i < 2; i++)
	{
		for (auto& [pos, on] : image)
		{
			convolve.reset();
		}
	}

	//std::cout << "Part 1: " << count << std::endl;

	//std::cout << "Part 2: " << count << std::endl;
}
