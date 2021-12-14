// Day12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Node.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <map>
#include <memory>
#include <regex>

int main()
{
	std::filesystem::path input("input.txt");

	std::ifstream inStrm;
	inStrm.open(input);

	std::regex nodePairs("([a-zA-Z]+)-([a-zA-Z]+)");
	std::map<std::string, std::shared_ptr<Node>> caves;

	std::string line;
	while (inStrm >> line)
	{
		std::smatch m;
		std::regex_match(line, m, nodePairs);

		if (!caves.contains(m[1]))
		{
			caves.emplace(m[1], std::make_shared<Node>(m[1]));
		}

		if (!caves.contains(m[2]))
		{
			caves.emplace(m[2], std::make_shared<Node>(m[2]));
		}

		auto cave1 = caves[m[1]];
		auto cave2 = caves[m[2]];

		cave1->AddNeighbour(cave2);
	}

	Node::Route route;
	auto startCave = caves["start"];
	startCave->TravelTo(route);

	std::cout << "Part 1: " << caves["end"]->GetRoutes().size() << std::endl;

	for (auto& [name, node] : caves)
	{
		node->ResetRoutes();
	}

	startCave->TravelTo(route, false);

	std::cout << "Part 2: " << caves["end"]->GetRoutes().size() << std::endl;
}
