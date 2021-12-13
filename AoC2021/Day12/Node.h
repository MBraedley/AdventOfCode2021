#pragma once

#include <memory>
#include <set>
#include <string>
#include <queue>

class Node :std::enable_shared_from_this<Node>
{
public:
	Node(std::string name);

	void AddNeighbour(std::shared_ptr<Node> neighbour);

	virtual bool TravelTo(std::queue<std::shared_ptr<Node>> route);
	bool CanEnter() { return m_CanEnter; }

private:
	std::string m_Name;
	std::set<std::shared_ptr<Node>> m_Neighbours;

	bool m_CanEnter = true;
	bool m_IsSmall = false;
};

class EndNode : Node
{
public:
	EndNode(std::string name);

	virtual bool TravelTo(std::queue<std::shared_ptr<Node>> route) override;

	std::uint32_t GetCompletedRoutes() { return m_CompletedRoutes; }

private:
	std::uint32_t m_CompletedRoutes = 0;
};
