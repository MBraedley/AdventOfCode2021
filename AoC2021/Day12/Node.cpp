#include "Node.h"

#include <regex>
#include <cassert>

Node::Node(std::string name) :
	m_Name(name)
{
	std::regex small("[a-z]+");
	m_IsSmall = std::regex_match(m_Name, small);
}

void Node::AddNeighbour(std::shared_ptr<Node> neighbour)
{
	if (!m_Neighbours.contains(neighbour))
	{
		m_Neighbours.insert(neighbour);
		neighbour->AddNeighbour(shared_from_this());
	}
}

bool Node::TravelTo(Route route)
{
	if (m_IsSmall && std::find(route.begin(), route.end(), shared_from_this()) != route.end())
	{
		return false;
	}

	route.push_back(shared_from_this());
	m_RoutesToHere.push_back(route);

	if (m_Name == "end")
	{
		return true;
	}

	bool reachedEnd = false;
	for (auto& node : m_Neighbours)
	{
		if (node->TravelTo(route))
		{
			reachedEnd = true;
		}
	}

	return reachedEnd;
}

bool Node::TravelTo(Route route, bool smallDone)
{
	auto countThisCave = std::count(route.begin(), route.end(), shared_from_this());
	if (m_IsSmall && (countThisCave == 2 || countThisCave == 1 && smallDone))
	{
		return false;
	}

	if (m_IsSmall && countThisCave == 1)
	{
		assert(!smallDone);
		smallDone = true;
	}

	if (m_Name == "start" && !route.empty())
	{
		return false;
	}

	route.push_back(shared_from_this());
	m_RoutesToHere.push_back(route);

	if (m_Name == "end")
	{
		return true;
	}

	bool reachedEnd = false;
	for (auto& node : m_Neighbours)
	{
		if (node->TravelTo(route, smallDone))
		{
			reachedEnd = true;
		}
	}

	return reachedEnd;
}
