#pragma once
#include <iostream>
#include <set>
#include <optional>

struct BeaconDistance
{
	int dx;
	int dy;
	int dz;
};

struct BeaconCoords
{
	int x;
	int y;
	int z;

	BeaconCoords& operator+=(const BeaconDistance& dist)
	{
		x += dist.dx;
		y += dist.dy;
		z += dist.dz;

		return *this;
	}
};

auto operator<=>(const BeaconCoords& lhs, const BeaconCoords& rhs);
auto operator<=>(const BeaconDistance& lhs, const BeaconDistance& rhs);
BeaconCoords operator+(const BeaconCoords& lhs, const BeaconDistance& rhs);
BeaconDistance operator-(const BeaconCoords& lhs, const BeaconCoords& rhs);

class Scanner
{
public:
	Scanner() = default;
	Scanner(int id);

	void AddBeacon(const BeaconCoords& beacon);

	Scanner RotateX();
	Scanner RotateY();
	Scanner RotateZ();

	std::optional<BeaconDistance> GetScannerOverlap(const Scanner& other);
	void MergeScanner(const Scanner& other, const BeaconDistance& dist );

	friend std::istream& operator>>(std::istream& inStrm, Scanner& scanner);
private:
	int m_Id = 0;
	std::set<BeaconCoords> m_VisibleBeacons;
};

