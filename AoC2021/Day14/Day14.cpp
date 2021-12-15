// Day14.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include <list>
#include <map>
#include <regex>
#include <cassert>

int main()
{
	std::filesystem::path input("input.txt");

	std::ifstream inStrm;
	inStrm.open(input);

	std::string basePolymer;
	std::getline(inStrm, basePolymer);

	std::map<char, std::uint64_t> baseCounts;
	std::map<std::pair<char, char>, std::uint64_t> basePairs;

	for (auto iter = basePolymer.begin(); iter != basePolymer.end(); iter++)
	{
		baseCounts[*iter]++;
		if (iter + 1 != basePolymer.end())
		{
			char c1 = *iter;
			char c2 = *(iter + 1);
			basePairs[std::make_pair(c1, c2)]++;
		}
	}

	std::map<std::pair<char, char>, char> insertionRules;

	std::string line;
	std::getline(inStrm, line);	//empty line
	
	std::regex rule("([A-Z])([A-Z])[^A-Z]+([A-Z])");
	std::smatch m;
	while (std::getline(inStrm, line))
	{
		bool matched = std::regex_match(line, m, rule);
		assert(matched);
		insertionRules.emplace(std::make_pair( m[1].str()[0], m[2].str()[0]), m[3].str()[0]);
	}

	for (int i = 0; i < 10; i++)
	{
		std::map<std::pair<char, char>, std::uint64_t> nextPairs;
		for (auto& [p, c] : basePairs)
		{
			assert(insertionRules.contains(p));
			auto n = insertionRules[p];
			nextPairs[std::make_pair(p.first, n)] += c;
			nextPairs[std::make_pair(n, p.second)] += c;
			baseCounts[n] += c;
		}
		std::swap(basePairs, nextPairs);
	}
	
	std::uint64_t countA = 0;
	std::uint64_t countB = std::numeric_limits<std::uint64_t>::max();

	for (auto& [base, count] : baseCounts)
	{
		if (count > countA)
		{
			countA = count;
		}

		if (count < countB)
		{
			countB = count;
		}
	}

	std::cout << "Part 1: " << countA - countB << std::endl;

	for (int i = 10; i < 40; i++)
	{
		std::map<std::pair<char, char>, std::uint64_t> nextPairs;
		for (auto& [p, c] : basePairs)
		{
			assert(insertionRules.contains(p));
			auto n = insertionRules[p];
			nextPairs[std::make_pair(p.first, n)] += c;
			nextPairs[std::make_pair(n, p.second)] += c;
			baseCounts[n] += c;
		}
		std::swap(basePairs, nextPairs);
	}

	countA = 0;
	countB = std::numeric_limits<std::uint64_t>::max();

	for (auto& [base, count] : baseCounts)
	{
		if (count > countA)
		{
			countA = count;
		}

		if (count < countB)
		{
			countB = count;
		}
	}

	std::cout << "Part 2: " << countA - countB << std::endl;
}
