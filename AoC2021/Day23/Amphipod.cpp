#include "Amphipod.h"

Amphipod::Amphipod(std::uint32_t moveCost, std::pair<int, int> position, int destCol) :
    m_Pos(position),
    m_MoveCost(moveCost),
    m_DestCol(destCol)
{
}

Amphipod::Amphipod(const Amphipod& other) :
    m_Pos(other.m_Pos),
    m_MoveCost(other.m_MoveCost),
    m_MoveDist(other.m_MoveDist),
    m_DestCol(other.m_DestCol),
    m_MovedOnce(other.m_MovedOnce),
    m_MovedTwice(other.m_MovedTwice)
{
}

void Amphipod::MoveTo(std::pair<int, int> pos)
{
    m_MoveDist += std::abs(m_Pos.first - pos.first) + std::abs(m_Pos.second - pos.second);
    m_Pos = pos;
}

std::unique_ptr<Amphipod> Amphipod::Copy()
{
    return std::make_unique<Amphipod>(*this);
}
