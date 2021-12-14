#pragma once

#include <memory>
#include <set>
#include <string>
#include <vector>

class Node : public std::enable_shared_from_this<Node>
{
public:
	using Route = std::vector<std::shared_ptr<Node>>;

	Node(std::string name);

	void AddNeighbour(std::shared_ptr<Node> neighbour);

	bool TravelTo(Route route);
	bool TravelTo(Route route, bool smallDone);

	const std::string& GetName() { return m_Name; }

	const std::vector<Route>& GetRoutes() { return m_RoutesToHere; }

	void ResetRoutes() { m_RoutesToHere.clear(); }

private:
	std::string m_Name;
	std::set<std::shared_ptr<Node>> m_Neighbours;
	
	std::vector<Route> m_RoutesToHere;

	bool m_IsSmall = false;
};
