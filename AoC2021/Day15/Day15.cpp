// Day15.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <map>
#include <queue>

struct PosRisk
{
	std::pair<std::size_t, std::size_t> pos;
	std::uint32_t risk;
};

auto operator<=>(const PosRisk& lhs, const PosRisk& rhs)
{
	return lhs.risk <=> rhs.risk;
}

int main()
{
	std::filesystem::path input("input.txt");

	std::ifstream inStrm;
	inStrm.open(input);

	std::vector<std::vector<std::uint32_t>> map;
	std::string line;
	while (inStrm >> line)
	{
		std::vector<std::uint32_t> row;
		for (char c : line)
		{
			row.push_back(c - '0');
		}
		map.push_back(row);
	}
	
	std::map<std::pair<std::size_t, std::size_t>, std::uint32_t> risks;
	std::priority_queue<PosRisk, std::vector<PosRisk>, std::greater<PosRisk>> nextLocations;
	
	risks.emplace(std::make_pair<std::size_t, std::size_t>(0, 0), 0);
	nextLocations.emplace(std::make_pair<std::size_t, std::size_t>(0, 1), 0);
	nextLocations.emplace(std::make_pair<std::size_t, std::size_t>(1, 0), 0);

	auto endPos = std::make_pair<std::size_t, std::size_t>(map[0].size() - 1, map.size() - 1);

	while (!nextLocations.empty())
	{
		auto [pos, risk] = nextLocations.top();
		risk += map[pos.second][pos.first];
		if (!risks.contains(pos) || risks[pos] > risk)
		{
			risks[pos] = risk;
			if (pos.first > 0)
			{
				auto nextPos = pos;
				nextPos.first--;
				nextLocations.push({ nextPos, risk });
			}

			if (pos.second > 0)
			{
				auto nextPos = pos;
				nextPos.second--;
				nextLocations.push({ nextPos, risk });
			}

			if (pos.first < map[0].size() - 1)
			{
				auto nextPos = pos;
				nextPos.first++;
				nextLocations.push({ nextPos, risk });
			}

			if (pos.second < map.size() - 1)
			{
				auto nextPos = pos;
				nextPos.second++;
				nextLocations.push({ nextPos, risk });
			}
		}

		nextLocations.pop();

		if (pos == endPos)
		{
			break;
		}
	}

	std::uint32_t risk = risks[endPos];

	std::cout << "Part 1: " << risk << std::endl;

	//std::cout << "Part 2: " << count << std::endl;
}
