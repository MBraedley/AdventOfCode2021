// Day23.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Hallway.h"
#include "Room.h"
#include "Amphipod.h"

#include <iostream>
#include <thread>
#include <optional>
#include <cassert>

int main()
{
	std::array<std::unique_ptr<Room>, 4> rooms;
	rooms[0] = std::make_unique<Room>(
		2,
		std::make_unique<Amphipod>(1, std::make_pair<int, int>(2, 1), 2),
		std::make_unique<Amphipod>(10, std::make_pair<int, int>(2, 2), 4));
	rooms[1] = std::make_unique<Room>(
		4,
		std::make_unique<Amphipod>(1000, std::make_pair<int, int>(4, 1), 8),
		std::make_unique<Amphipod>(100, std::make_pair<int, int>(4, 2), 6));
	rooms[2] = std::make_unique<Room>(
		6,
		std::make_unique<Amphipod>(10, std::make_pair<int, int>(6, 1), 4),
		std::make_unique<Amphipod>(1, std::make_pair<int, int>(6, 2), 2));
	rooms[3] = std::make_unique<Room>(
		8,
		std::make_unique<Amphipod>(1000, std::make_pair<int, int>(8, 1), 8),
		std::make_unique<Amphipod>(100, std::make_pair<int, int>(8, 2), 6));

	Hallway hall(std::move(rooms));

	auto score = hall.TryAllNextMoves();
	assert(score.has_value());

	std::cout << "Part 1: " << score.value() << std::endl;

	//std::cout << "Part 2: " << count << std::endl;
}
