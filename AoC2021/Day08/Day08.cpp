// Day08.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <array>

struct Display
{
	std::array<std::string, 10> m_EachDigit;
	std::array<std::string, 4> m_Output;
};

std::istream& operator>>(std::istream& in, Display& obj)
{
	std::string delim;
	for (std::uint32_t i = 0; i < 10; i++)
	{
		in >> obj.m_EachDigit[i];
	}
	in >> delim;
	for (std::uint32_t i = 0; i < 4; i++)
	{
		in >> obj.m_Output[i];
	}

	return in;
}

int main()
{
	std::filesystem::path input("input.txt");

	std::ifstream inStrm;
	inStrm.open(input);

	std::vector<Display> values;
	Display val;
	while (inStrm >> val)
	{
		values.push_back(val);
	}

	std::uint32_t count = 0;
	for (auto& dis : values)
	{
		count += std::count_if(dis.m_Output.begin(), dis.m_Output.end(), [](std::string& ssd) -> bool
			{
				auto len = ssd.size();
				return len == 2 || len == 3 || len == 4 || len == 7;
			});
	}

	std::cout << "Part 1: " << count << std::endl;


//	std::cout << "Part 2: " << count << std::endl;
}
