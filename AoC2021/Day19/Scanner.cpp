#include "Scanner.h"

#include <regex>

Scanner::Scanner(int id) :
	m_Id(id)
{
}

void Scanner::AddBeacon(const BeaconCoords& beacon)
{
	m_VisibleBeacons.push_back(beacon);
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
