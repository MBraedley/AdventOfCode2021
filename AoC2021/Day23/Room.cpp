#include "Room.h"

#include <cassert>

Room::Room(int id, std::unique_ptr<Amphipod> top, std::unique_ptr<Amphipod> bottom) :
	m_Id(id),
	m_Top(std::move(top)),
	m_Bottom(std::move(bottom))
{
}

Room::Room(const Room& other) :
	m_Id(other.m_Id)
{
	if (other.m_Top)
	{
		m_Top = other.m_Top->Copy();
	}

	if (other.m_Bottom)
	{
		m_Bottom = other.m_Bottom->Copy();
	}
}

Room::Room(Room&& other) noexcept :
	m_Id(other.m_Id),
	m_Top(std::move(other.m_Top)),
	m_Bottom(std::move(other.m_Bottom))
{
}

bool Room::CanMoveIn(const Amphipod& pod) const
{
	if ((m_Bottom == nullptr || m_Bottom->GetDestination() == m_Id) && m_Top == nullptr && pod.GetDestination() == m_Id)
	{
		return true;
	}

	return false;
}

bool Room::CanMoveOut() const
{
	bool ret = false;

	if (m_Top != nullptr)
	{
		ret = m_Top->GetDestination() != m_Id || m_Bottom->GetDestination() != m_Id;
	}
	else if (m_Bottom != nullptr)
	{
		ret = m_Bottom->GetDestination() != m_Id;
	}

	return ret;
}

void Room::MoveIn(std::unique_ptr<Amphipod>& pod)
{
	assert(m_Top == nullptr);
	assert(pod->GetDestination() == m_Id);
	assert(m_Bottom == nullptr || m_Bottom->GetDestination() == m_Id);

	if (m_Bottom == nullptr)
	{
		pod->MoveTo({ m_Id, 2 });
		m_Bottom.swap(pod);
	}
	else
	{
		pod->MoveTo({ m_Id, 1 });
		m_Top.swap(pod);
	}
}

std::unique_ptr<Amphipod> Room::MoveOut(int hallPos)
{
	std::unique_ptr<Amphipod> ret = nullptr;
	
	if (m_Top != nullptr)
	{
		ret.swap(m_Top);
	}
	else if (m_Bottom != nullptr)
	{
		ret.swap(m_Bottom);
	}

	assert(ret != nullptr);
	ret->MoveTo({hallPos, 0});

	return ret;
}

bool Room::IsFinished() const
{
	return m_Bottom != nullptr && m_Bottom->GetDestination() == m_Id && m_Top != nullptr && m_Top->GetDestination() == m_Id;
}

std::uint32_t Room::GetScore() const
{
	assert(IsFinished());
	return m_Bottom->GetScore() + m_Top->GetScore();
}

std::unique_ptr<Room> Room::Copy()
{
	return std::make_unique<Room>(*this);
}
