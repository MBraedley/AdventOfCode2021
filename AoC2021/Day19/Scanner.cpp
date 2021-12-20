#include "Scanner.h"

#include <regex>
#include <map>

auto operator<=>(const BeaconCoords& lhs, const BeaconCoords& rhs)
{
	if (lhs.x == rhs.x)
	{
		if (lhs.y == rhs.y)
		{
			return lhs.z <=> rhs.z;
		}
		return lhs.y <=> rhs.y;
	}
	return lhs.x <=> rhs.x;
}

auto operator<=>(const BeaconDistance& lhs, const BeaconDistance& rhs)
{
	if (lhs.dx == rhs.dx)
	{
		if (lhs.dy == rhs.dy)
		{
			return lhs.dz <=> rhs.dz;
		}
		return lhs.dy <=> rhs.dy;
	}
	return lhs.dx <=> rhs.dx;
}

BeaconCoords operator+(const BeaconCoords& lhs, const BeaconDistance& rhs)
{
	BeaconCoords coords;
	coords.x = lhs.x + rhs.dx;
	coords.y = lhs.y + rhs.dy;
	coords.z = lhs.z + rhs.dz;

	return coords;
}

BeaconDistance operator-(const BeaconCoords& lhs, const BeaconCoords& rhs)
{
	BeaconDistance dist;
	dist.dx = lhs.x - rhs.x;
	dist.dy = lhs.y - rhs.y;
	dist.dz = lhs.z - rhs.z;

	return dist;
}

Scanner::Scanner(int id) :
	m_Id(id)
{
}

void Scanner::AddBeacon(const BeaconCoords& beacon)
{
	m_VisibleBeacons.insert(beacon);
}

Scanner Scanner::RotateX()
{
	Scanner rot(m_Id);

	for (auto& coords : m_VisibleBeacons)
	{
		rot.AddBeacon({ coords.x, coords.z, -coords.y });
	}

	return rot;
}

Scanner Scanner::RotateY()
{
	Scanner rot(m_Id);

	for (auto& coords : m_VisibleBeacons)
	{
		rot.AddBeacon({ -coords.z, coords.y, coords.x });
	}

	return rot;
}

Scanner Scanner::RotateZ()
{
	Scanner rot(m_Id);

	for (auto& coords : m_VisibleBeacons)
	{
		rot.AddBeacon({ coords.y, -coords.x, coords.z });
	}

	return rot;
}

std::optional<BeaconDistance> Scanner::GetScannerOverlap(const Scanner& other)
{
	std::map<BeaconDistance, std::uint32_t> distCounts;

	for (auto& lPoint : m_VisibleBeacons)
	{
		for (auto& rPoint : other.m_VisibleBeacons)
		{
			auto dist = lPoint - rPoint;
			distCounts[dist]++;
			if (distCounts[dist] >= 12)
			{
				return dist;
			}
		}
	}

	return std::nullopt;
}

void Scanner::MergeScanner(const Scanner& other, const BeaconDistance& dist)
{
	for (const auto& beacon : other.m_VisibleBeacons)
	{
		AddBeacon(beacon + dist);
	}
}

std::istream& operator>>(std::istream& inStrm, Scanner& scanner)
{
	scanner.m_VisibleBeacons.clear();
	std::regex idSearch("scanner ([0-9]+)");
	std::smatch m;
	std::string line;
	std::getline(inStrm, line);
	if (!std::regex_search(line, m, idSearch))
	{
		inStrm.setstate(std::ios::failbit);
		return inStrm;
	}

	scanner.m_Id = std::stoi(m[1]);

	std::regex coordsMatch("(-?[0-9]+),(-?[0-9]+),(-?[0-9]+)");
	while (std::getline(inStrm, line) && !line.empty())
	{
		if (!std::regex_match(line, m, coordsMatch))
		{
			inStrm.setstate(std::ios::failbit);
			return inStrm;
		}

		scanner.AddBeacon({ std::stoi(m[1]), std::stoi(m[2]), std::stoi(m[3]) });
	}

	return inStrm;
}
