// Day08.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <array>
#include <set>
#include <map>

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
		std::sort(obj.m_EachDigit[i].begin(), obj.m_EachDigit[i].end());
	}
	in >> delim;
	for (std::uint32_t i = 0; i < 4; i++)
	{
		in >> obj.m_Output[i];
		std::sort(obj.m_Output[i].begin(), obj.m_Output[i].end());
	}

	return in;
}

bool ContainsAll(std::string super, std::string sub)
{
	for (auto c : sub)
	{
		if (super.find(c) == std::string::npos)
		{
			return false;
		}
	}
	return true;
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

	std::uint32_t fullOutput = 0;

	for (const auto& dis : values)
	{
		std::set<std::string> allVals(dis.m_EachDigit.begin(), dis.m_EachDigit.end());
		std::map<std::string, int> str2Int;
		std::map<int, std::string> int2Str;

		auto digit1 = std::find_if(allVals.begin(), allVals.end(), [](std::string str) -> bool
			{
				return str.length() == 2;
			});

		str2Int.emplace(*digit1, 1);
		int2Str.emplace(1, *digit1);
		allVals.erase(digit1);

		auto digit4 = std::find_if(allVals.begin(), allVals.end(), [](std::string str) -> bool
			{
				return str.length() == 4;
			});

		str2Int.emplace(*digit4, 4);
		int2Str.emplace(4, *digit4);
		allVals.erase(digit4);

		auto digit7 = std::find_if(allVals.begin(), allVals.end(), [](std::string str) -> bool
			{
				return str.length() == 3;
			});

		str2Int.emplace(*digit7, 7);
		int2Str.emplace(7, *digit7);
		allVals.erase(digit7);

		auto digit8 = std::find_if(allVals.begin(), allVals.end(), [](std::string str) -> bool
			{
				return str.length() == 7;
			});

		str2Int.emplace(*digit8, 8);
		int2Str.emplace(8, *digit8);
		allVals.erase(digit8);

		auto digit3 = std::find_if(allVals.begin(), allVals.end(), [str7 = int2Str[7]](std::string str) -> bool
		{
			if (str.length() == 5)
			{
				return ContainsAll(str, str7);
			}
			else
			{
				return false;
			}
		});

		str2Int.emplace(*digit3, 3);
		int2Str.emplace(3, *digit3);
		allVals.erase(digit3);

		auto digit9 = std::find_if(allVals.begin(), allVals.end(), [str7 = int2Str[7], str3 = int2Str[3], str4 = int2Str[4]](std::string str) -> bool
			{
				if (str.length() == 6)
				{
					return ContainsAll(str, str7) && ContainsAll(str, str3) && ContainsAll(str, str4);
				}
				else
				{
					return false;
				}
			});

		str2Int.emplace(*digit9, 9);
		int2Str.emplace(9, *digit9);
		allVals.erase(digit9);

		auto digit5 = std::find_if(allVals.begin(), allVals.end(), [str9 = int2Str[9]](std::string str) -> bool
		{
			if (str.length() == 5)
			{
				return ContainsAll(str9, str);
			}
			else
			{
				return false;
			}
		});

		str2Int.emplace(*digit5, 5);
		int2Str.emplace(5, *digit5);
		allVals.erase(digit5);

		auto digit6 = std::find_if(allVals.begin(), allVals.end(), [str5 = int2Str[5]](std::string str) -> bool
			{
				if (str.length() == 6)
				{
					return ContainsAll(str, str5);
				}
				else
				{
					return false;
				}
			});

		str2Int.emplace(*digit6, 6);
		int2Str.emplace(6, *digit6);
		allVals.erase(digit6);

		auto digit0 = std::find_if(allVals.begin(), allVals.end(), [](std::string str) -> bool
			{
				return str.length() == 6;
			});

		str2Int.emplace(*digit0, 0);
		int2Str.emplace(0, *digit0);
		allVals.erase(digit0);

		auto digit2 = std::find_if(allVals.begin(), allVals.end(), [](std::string str) -> bool
			{
				return str.length() == 5;
			});

		str2Int.emplace(*digit2, 2);
		int2Str.emplace(2, *digit2);
		allVals.erase(digit2);

		fullOutput += 1000 * str2Int[dis.m_Output[0]] + 100 * str2Int[dis.m_Output[1]] + 10 * str2Int[dis.m_Output[2]] + str2Int[dis.m_Output[3]];
	}

	std::cout << "Part 2: " << fullOutput << std::endl;
}
