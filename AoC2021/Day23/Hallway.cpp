#include "Hallway.h"

#include <vector>
#include <future>
#include <cassert>

Hallway::Hallway(std::array<std::unique_ptr<Room>, 4> rooms) :
	m_Rooms(std::move(rooms))
{
}

Hallway::Hallway(const Hallway& other)
{
	for (std::size_t i = 0; i < m_HallSpaces.size(); i++)
	{
		if (other.m_HallSpaces[i])
		{
			m_HallSpaces[i] = other.m_HallSpaces[i]->Copy();
		}
	}

	for (std::size_t i = 0; i < m_Rooms.size(); i++)
	{
		m_Rooms[i] = other.m_Rooms[i]->Copy();
	}
}

std::unique_ptr<Hallway> Hallway::Copy()
{
	return std::make_unique<Hallway>(*this);
}

std::optional<std::uint32_t> Hallway::TryMoveToRoom(std::size_t hallway, std::size_t room)
{
	//if (m_HallSpaces[hallway] == nullptr)
	//{
	//	return std::nullopt;	//Nobody there
	//}

	//if (!m_Rooms[room]->CanMoveIn(*m_HallSpaces[hallway]))
	//{
	//	return std::nullopt;	//Can't move to that room
	//}

	//for (std::size_t i = std::min(hallway, room * 2 + 2) + 1; i < std::max(hallway, room * 2 + 2); i++)
	//{
	//	if (m_HallSpaces[i] != nullptr)
	//	{
	//		return std::nullopt;	//Hallway blocked
	//	}
	//}

	m_Rooms[room]->MoveIn(m_HallSpaces[hallway]);

	if (IsFinished())
	{
		return GetScore();
	}

	return TryAllNextMoves();
}

std::optional<std::uint32_t> Hallway::TryMoveToHallway(std::size_t room, std::size_t hallway)
{
	//if (!m_Rooms[room]->CanMoveOut())
	//{
	//	return std::nullopt;
	//}

	//if (m_HallSpaces[hallway] != nullptr)
	//{
	//	return std::nullopt;	//Space already occupied
	//}

	//for (std::size_t i = std::min(hallway, room * 2 + 2) + 1; i < std::max(hallway, room * 2 + 2); i++)
	//{
	//	if (m_HallSpaces[i] != nullptr)
	//	{
	//		return std::nullopt;	//Hallway blocked
	//	}
	//}

	m_HallSpaces[hallway] = m_Rooms[room]->MoveOut(hallway);

	if (IsBlocked())
	{
		return std::nullopt;
	}

	return TryAllNextMoves();
}

bool Hallway::IsFinished() const
{
	for (const auto& room : m_Rooms)
	{
		if (!room->IsFinished())
		{
			return false;
		}
	}
	return true;
}

std::uint32_t Hallway::GetScore() const
{
	assert(IsFinished());
	std::uint32_t score = 0;
	for (const auto& room : m_Rooms)
	{
		score += room->GetScore();
	}
	return score;
}

std::optional<std::uint32_t> Hallway::TryAllNextMoves()
{
	std::vector<std::future<std::optional<std::uint32_t>>> futures;

	for (std::size_t hallPos : {0, 1, 3, 5, 7, 9, 10})	//Not allowed to stop outside a room
	{
		for (std::size_t room = 0; room < m_Rooms.size(); room++)
		{
			if (IsPathOpen(hallPos, room))
			{
				if (m_HallSpaces[hallPos] != nullptr)
				{
					if (m_Rooms[room]->CanMoveIn(*m_HallSpaces[hallPos]))
					{
						std::packaged_task<std::optional<std::uint32_t>(std::unique_ptr<Hallway>, std::size_t, std::size_t)> task(
							[](std::unique_ptr<Hallway> hallway, std::size_t hallPos, std::size_t room)->std::optional<std::uint32_t>
							{
								return hallway->TryMoveToRoom(hallPos, room);
							});
						futures.push_back(task.get_future());
						std::thread t(std::move(task), Copy(), hallPos, room);
						t.detach();
					}
				}
				else
				{
					if (m_Rooms[room]->CanMoveOut())
					{
						std::packaged_task<std::optional<std::uint32_t>(std::unique_ptr<Hallway>, std::size_t, std::size_t)> task(
							[](std::unique_ptr<Hallway> hallway, std::size_t hallPos, std::size_t room)->std::optional<std::uint32_t>
							{
								return hallway->TryMoveToHallway(room, hallPos);
							});
						futures.push_back(task.get_future());
						std::thread t(std::move(task), Copy(), hallPos, room);
						t.detach();
					}
				}
			}
		}
	}

	std::uint32_t minCompletion = std::numeric_limits<std::uint32_t>::max();
	std::optional<std::uint32_t> ret = std::nullopt;

	for (auto& future : futures)
	{
		future.wait();
		auto result = future.get();
		if (result.has_value() && result.value() < minCompletion)
		{
			minCompletion = result.value();
			ret = result;
		}
	}

	return ret;
}

bool Hallway::IsBlocked()
{
	for (std::size_t i = 0; i < m_HallSpaces.size() - 1; i++)
	{
		if (m_HallSpaces[i] != nullptr)
		{
			for (std::size_t j = i + 1; j < m_HallSpaces.size(); j++)
			{
				if (m_HallSpaces[j] != nullptr && m_HallSpaces[i]->GetDestination() > j && m_HallSpaces[j]->GetDestination() < i)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Hallway::IsPathOpen(std::size_t hallPos, std::size_t room)
{
	for (std::size_t i = std::min(hallPos, room * 2 + 2) + 1; i < std::max(hallPos, room * 2 + 2); i++)
	{
		if (m_HallSpaces[i] != nullptr)
		{
			return false;	//Hallway blocked
		}
	}
	return true;
}
