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

bool Node::TravelTo(std::queue<std::shared_ptr<Node>> route)
{
	assert(m_CanEnter);
	route.push(shared_from_this());
	if (m_IsSmall)
	{
		m_CanEnter = false;
	}

	bool reachedEnd = false;
	for (auto& node : m_Neighbours)
	{
		if (node->CanEnter() && node->TravelTo(route))
		{
			reachedEnd = true;
		}
	}
}

EndNode::EndNode(std::string name) :
	Node(name)
{
}

bool EndNode::TravelTo(std::queue<std::shared_ptr<Node>> route)
{
	m_CompletedRoutes++;
	return true;
}
