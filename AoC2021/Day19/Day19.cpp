// Day19.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Scanner.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <queue>
#include <set>

int main()
{
	std::filesystem::path input("input.txt");

	std::ifstream inStrm;
	inStrm.open(input);

	std::queue<Scanner> scanners;
	
	for (Scanner s; inStrm >> s;)
	{
		scanners.push(s);
	}

	Scanner primary = scanners.front();
	scanners.pop();

	while (!scanners.empty())
	{
		Scanner secondary = scanners.front();
		scanners.pop();
		if (auto dist = primary.GetScannerOverlap(secondary); dist.has_value())
		{
			primary.MergeScanner(secondary, dist.value());
			continue;
		}

		secondary.RotateX();
		if (auto dist = primary.GetScannerOverlap(secondary); dist.has_value())
		{
			primary.MergeScanner(secondary, dist.value());
			continue;
		}

		secondary.RotateY();
		//Give up for now, we'll come back to it
		scanners.push(secondary);
	}

	std::cout << "Part 1: " << scanners.size() << std::endl;


	//std::cout << "Part 2: " << count << std::endl;
}
