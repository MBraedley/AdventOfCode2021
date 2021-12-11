#include "Octopus.h"

Octopus::Octopus(std::uint32_t startingEnergy) :
	m_Energy(startingEnergy)
{
}

void Octopus::AddNeighbour(std::shared_ptr<Octopus> neighbour)
{
	if (!m_Neighbours.contains(neighbour))
	{
		m_Neighbours.insert(neighbour);
		neighbour->AddNeighbour(shared_from_this());
	}
}

void Octopus::Step()
{
	m_Energy++;
	CheckIfFlashed();
}

bool Octopus::Flashed()
{
	if (m_FlashedThisStep)
	{
		m_FlashedThisStep = false;
		m_Energy = 0;
		return true;
	}
	return false;
}

void Octopus::NeighbourFlashed()
{
	m_Energy++;
	CheckIfFlashed();
}

void Octopus::CheckIfFlashed()
{
	if (m_Energy >= 10 && !m_FlashedThisStep)
	{
		m_FlashedThisStep = true;
		for (auto& neighbour : m_Neighbours)
		{
			neighbour->NeighbourFlashed();
		}
	}
}
