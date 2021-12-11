#pragma once
#include <memory>
#include <set>

class Octopus : public std::enable_shared_from_this<Octopus>
{
public:
	Octopus(std::uint32_t startingEnergy);
	~Octopus() = default;

	void AddNeighbour(std::shared_ptr<Octopus> neighbour);

	void Step();
	bool Flashed();

private:
	void NeighbourFlashed();
	void CheckIfFlashed();

	std::set<std::shared_ptr<Octopus>> m_Neighbours;

	std::uint32_t m_Energy = 0;
	bool m_FlashedThisStep = false;
};

