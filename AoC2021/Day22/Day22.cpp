// Day22.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <regex>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <cassert>

struct PowerUpStep
{
	bool turnOn;
	std::pair<int, int> xRange;
	std::pair<int, int> yRange;
	std::pair<int, int> zRange;
};

struct Coord3d
{
	int x;
	int y;
	int z;
};

template<>
struct std::hash<Coord3d>
{
	std::size_t operator()(Coord3d const& pos) const noexcept
	{
		auto hx = std::hash<int>{}(pos.x);
		auto hy = std::hash<int>{}(pos.y);
		auto hz = std::hash<int>{}(pos.z);

		return (hx << 2) ^ (hy << 1) ^ hz;
	}
};

bool operator==(const Coord3d& lhs, const Coord3d& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

int main()
{
	std::filesystem::path input("input.txt");

	std::ifstream inStrm;
	inStrm.open(input);

	std::vector<PowerUpStep> steps;
	std::regex rPowerUp("(on|off) x=(-?[0-9]+)\\.\\.(-?[0-9]+),y=(-?[0-9]+)\\.\\.(-?[0-9]+),z=(-?[0-9]+)\\.\\.(-?[0-9]+)");

	for (std::string line; std::getline(inStrm, line);)
	{
		std::smatch m;
		bool matched = std::regex_match(line, m, rPowerUp);
		assert(matched);

		steps.emplace_back(
			m[1] == "on",
			std::make_pair<int, int>(std::stoi(m[2]), std::stoi(m[3])),
			std::make_pair<int, int>(std::stoi(m[4]), std::stoi(m[5])),
			std::make_pair<int, int>(std::stoi(m[6]), std::stoi(m[7])));
	}

	std::unordered_set<Coord3d> reactor;

	for (const auto& step : steps)
	{
		if (std::abs(step.xRange.first) > 50)
		{
			break;
		}

		assert(step.xRange.first <= step.xRange.second);
		assert(step.yRange.first <= step.yRange.second);
		assert(step.zRange.first <= step.zRange.second);
		for (int x = step.xRange.first; x <= step.xRange.second; x++)
		{
			for (int y = step.yRange.first; y <= step.yRange.second; y++)
			{
				for (int z = step.zRange.first; z <= step.zRange.second; z++)
				{
					Coord3d pos{ x, y, z };
					if (step.turnOn)
					{
						reactor.insert(pos);
					}
					else
					{
						reactor.erase(pos);
					}
				}
			}
		}
	}

	std::cout << "Part 1: " << reactor.size() << std::endl;

	reactor.clear();
	for (const auto& step : steps)
	{
		assert(step.xRange.first <= step.xRange.second);
		assert(step.yRange.first <= step.yRange.second);
		assert(step.zRange.first <= step.zRange.second);
		for (int x = step.xRange.first; x <= step.xRange.second; x++)
		{
			for (int y = step.yRange.first; y <= step.yRange.second; y++)
			{
				for (int z = step.zRange.first; z <= step.zRange.second; z++)
				{
					Coord3d pos{ x, y, z };
					if (step.turnOn)
					{
						reactor.insert(pos);
					}
					else
					{
						reactor.erase(pos);
					}
				}
			}
		}
	}

	std::cout << "Part 2: " << reactor.size() << std::endl;
}
