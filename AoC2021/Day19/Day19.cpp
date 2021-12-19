// Day19.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Scanner.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <set>

int main()
{
	std::filesystem::path input("input.txt");

	std::ifstream inStrm;
	inStrm.open(input);

	std::vector<Scanner> scanners;
	
	for (Scanner s; inStrm >> s;)
	{
		scanners.push_back(s);
	}

	std::cout << "Part 1: " << scanners.size() << std::endl;


	//std::cout << "Part 2: " << count << std::endl;
}
