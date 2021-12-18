// Day18.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "SnailNumber.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <queue>

int main()
{
	std::filesystem::path input("input.txt");

	std::ifstream inStrm;
	inStrm.open(input);

	std::queue<SnailNumber> values;
	std::string val;
	while (inStrm >> val)
	{
		values.emplace(val);
	}

	SnailNumber sum = values.front();
	values.pop();

	while (!values.empty())
	{
		//std::cout << sum.ToString() << " + " << values.front().ToString();
		sum = sum + values.front();
		values.pop();
		//std::cout << " = " << sum.ToString() << std::endl;
	}

	std::cout << "Part 1: " << sum.GetMagnitude() << std::endl;


	//std::cout << "Part 2: " << count << std::endl;
}
