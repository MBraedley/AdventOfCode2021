// Day19.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Scanner.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <deque>
#include <set>

int main()
{
	std::filesystem::path input("input.txt");

	std::ifstream inStrm;
	inStrm.open(input);

	std::deque<Scanner> scanners;
	
	for (Scanner s; inStrm >> s;)
	{
		scanners.push_back(s);
	}

	while (scanners.size() > 1)
	{
		Scanner primary = scanners.front();
		scanners.pop_front();

		std::deque<Scanner> nextScanners;

		while (!scanners.empty())
		{
			auto secondary = scanners.front();
			scanners.pop_front();

			bool matchFound = false;
			for (std::size_t k = 0; !matchFound && k < 24; k++)
			{
				if (auto dist = primary.GetScannerOverlap(secondary); dist.has_value())
				{
					primary.MergeScanner(secondary, dist.value());
					matchFound = true;
				}
				else
				{
					secondary.IndexedRotation(k);
				}
			}

			if (!matchFound)
			{
				nextScanners.push_back(secondary);
			}
		}

		//Send this to the back to give others a chance
		nextScanners.push_back(primary);
		std::swap(scanners, nextScanners);
		std::cout << scanners.size() << std::endl;
	}

	std::cout << "Part 1: " << scanners.front().GetBeaconCount() << std::endl;


	std::cout << "Part 2: " << scanners.front().GetLargestDistance() << std::endl;
}
