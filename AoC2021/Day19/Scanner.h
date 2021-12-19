#pragma once
#include <iostream>
#include <vector>

struct BeaconCoords
{
	int x;
	int y;
	int z;
};

class Scanner
{
public:
	Scanner() = default;
	Scanner(int id);

	void AddBeacon(const BeaconCoords& beacon);

	friend std::istream& operator>>(std::istream& inStrm, Scanner& scanner);
private:
	int m_Id = 0;
	std::vector<BeaconCoords> m_VisibleBeacons;
};

