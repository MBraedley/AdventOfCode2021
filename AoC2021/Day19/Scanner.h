#pragma once
#include <iostream>
#include <set>
#include <map>
#include <optional>
#include <vector>
#include <functional>

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
BeaconDistance operator+(const BeaconDistance& lhs, const BeaconDistance& rhs);

class Scanner
{
public:
	Scanner() = default;
	Scanner(int id);

	void AddBeacon(const BeaconCoords& beacon);

	void IndexedRotation(std::size_t index);
	void RotateX();
	void RotateY();
	void RotateZ();

	std::optional<BeaconDistance> GetScannerOverlap(const Scanner& other);
	void MergeScanner(const Scanner& other, const BeaconDistance& dist);

	std::size_t GetBeaconCount() const { return m_VisibleBeacons.size(); }
	int GetLargestDistance() const;

	friend std::istream& operator>>(std::istream& inStrm, Scanner& scanner);
private:
	int m_Id = 0;
	std::set<BeaconCoords> m_VisibleBeacons;

	std::map<int, BeaconDistance> m_ScannerDistances;
};
