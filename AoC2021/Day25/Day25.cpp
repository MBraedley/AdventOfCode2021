// Day25.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <utility>
#include <unordered_set>

namespace std
{
	template<typename firstT, typename secondT>
	struct hash<pair<firstT, secondT>>
	{
		std::size_t operator()(pair<firstT, secondT> const& p) const noexcept
		{
			auto h1 = std::hash<firstT>{}(p.first);
			auto h2 = std::hash<secondT>{}(p.second);

			return (h1 << 1) ^ h2;
		}
	};
}

int main()
{
	std::filesystem::path input("input.txt");

	std::ifstream inStrm;
	inStrm.open(input);

	std::unordered_set<std::pair<std::size_t, std::size_t>> eastSC;
	std::unordered_set<std::pair<std::size_t, std::size_t>> southSC;
	std::size_t x = 0;
	std::size_t y = 0;
	for (std::string line; std::getline(inStrm, line);)
	{
		for (x = 0; x < line.size(); x++)
		{
			if (line[x] == '>')
			{
				eastSC.insert({ x, y });
			}

			if (line[x] == 'v')
			{
				southSC.insert({ x, y });
			}
		}
		y++;
	}

	std::size_t step = 0;
	bool scMoved = true;

	while (scMoved)
	{
		scMoved = false;
		std::unordered_set<std::pair<std::size_t, std::size_t>> nextEastSC;

		for (const auto& scPos : eastSC)
		{
			auto nextPos = scPos;
			nextPos.first++;
			if (nextPos.first >= x)
			{
				nextPos.first = 0;
			}

			if (!eastSC.contains(nextPos) && !southSC.contains(nextPos))
			{
				scMoved = true;
				nextEastSC.insert(nextPos);
			}
			else
			{
				nextEastSC.insert(scPos);
			}
		}

		std::swap(eastSC, nextEastSC);
		std::unordered_set<std::pair<std::size_t, std::size_t>> nextSouthSC;

		for (const auto& scPos : southSC)
		{
			auto nextPos = scPos;
			nextPos.second++;
			if (nextPos.second >= y)
			{
				nextPos.second = 0;
			}

			if (!eastSC.contains(nextPos) && !southSC.contains(nextPos))
			{
				scMoved = true;
				nextSouthSC.insert(nextPos);
			}
			else
			{
				nextSouthSC.insert(scPos);
			}
		}

		std::swap(southSC, nextSouthSC);

		step++;
	}

	std::cout << "Part 1: " << step << std::endl;

	//std::cout << "Part 2: " << count << std::endl;
}
