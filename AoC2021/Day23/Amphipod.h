#pragma once
#include <utility>
#include <memory>

class Amphipod
{
public:
	Amphipod(std::uint32_t moveCost, std::pair<int, int> position, int destCol);
	Amphipod(const Amphipod& other);
	
	const int GetDestination() const { return m_DestCol; };

	void MoveTo(std::pair<int, int> pos);

	std::uint32_t GetScore() const { return m_MoveCost * m_MoveDist; }

	[[nodiscard]] std::unique_ptr<Amphipod> Copy();

private:
	std::pair<int, int> m_Pos;
	const std::uint32_t m_MoveCost;
	std::uint32_t m_MoveDist = 0;
	const int m_DestCol;

	bool m_MovedOnce = false;
	bool m_MovedTwice = false;
};
