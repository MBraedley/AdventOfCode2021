#pragma once
#include "Amphipod.h"
#include "Room.h"

#include <array>
#include <memory>
#include <optional>

class Hallway
{
public:
	Hallway(std::array<std::unique_ptr<Room>, 4> rooms);
	Hallway(const Hallway& other);

	[[nodiscard]] std::unique_ptr<Hallway> Copy();

	std::optional<std::uint32_t> TryMoveToRoom(std::size_t hallway, std::size_t room);
	std::optional<std::uint32_t> TryMoveToHallway(std::size_t room, std::size_t hallway);

	bool IsFinished() const;
	std::uint32_t GetScore() const;

	std::optional<std::uint32_t> TryAllNextMoves();

private:
	bool IsBlocked();
	bool IsPathOpen(std::size_t hallPos, std::size_t room);

	std::array<std::unique_ptr<Room>, 4> m_Rooms;
	std::array<std::unique_ptr<Amphipod>, 11> m_HallSpaces;
};

