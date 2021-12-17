// Day16.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Packet.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <memory>
#include <map>
#include <deque>

int main()
{
	std::filesystem::path input("input.txt");

	std::ifstream inStrm;
	inStrm.open(input);

	const std::map<char, std::vector<bool>> hexLookup =
	{
		{'0', {false, false, false, false} },
		{'1', {false, false, false, true} },
		{'2', {false, false, true, false} },
		{'3', {false, false, true, true} },
		{'4', {false, true, false, false} },
		{'5', {false, true, false, true} },
		{'6', {false, true, true, false} },
		{'7', {false, true, true, true} },
		{'8', {true, false, false, false} },
		{'9', {true, false, false, true} },
		{'A', {true, false, true, false} },
		{'B', {true, false, true, true} },
		{'C', {true, true, false, false} },
		{'D', {true, true, false, true} },
		{'E', {true, true, true, false} },
		{'F', {true, true, true, true} },
	};

	std::string data;
	inStrm >> data;

	std::deque<bool> dataStrm;
	for (char c : data)
	{
		dataStrm.insert(dataStrm.end(), hexLookup.at(c).cbegin(), hexLookup.at(c).end());
	}

	Packet p(dataStrm);

	std::cout << "Part 1: " << p.GetVerionSum() << std::endl;

	std::cout << "Part 2: " << p.GetValue() << std::endl;
}
