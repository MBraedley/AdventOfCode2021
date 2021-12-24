#pragma once
#include "Amphipod.h"

#include <memory>

class Room
{
public:
	Room(int id, std::unique_ptr<Amphipod> top, std::unique_ptr<Amphipod> bottom);
	Room(const Room& other);
	Room(Room&& other) noexcept;

	bool CanMoveIn(const Amphipod& pod) const;
	bool CanMoveOut() const;

	void MoveIn(std::unique_ptr<Amphipod>& pod);
	[[nodiscard]] std::unique_ptr<Amphipod> MoveOut(int hallPos);

	bool IsFinished() const;
	std::uint32_t GetScore() const;

	[[nodiscard]] std::unique_ptr<Room> Copy();

private:
	const int m_Id;

	std::unique_ptr<Amphipod> m_Top;
	std::unique_ptr<Amphipod> m_Bottom;
};

