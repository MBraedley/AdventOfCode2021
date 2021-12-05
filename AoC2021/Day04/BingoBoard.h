#pragma once

#include <array>
#include <iostream>

class BingoBoard
{
public:
	BingoBoard() = default;
	virtual ~BingoBoard() = default;

	bool CallNumber(std::uint16_t num);
	bool IsWinner();
	std::uint32_t GetPartialScore();

	friend std::istream& operator>>(std::istream& in, BingoBoard& board);
	friend std::ostream& operator<<(std::ostream& out, BingoBoard& board);
private:
	std::array<std::array<std::uint16_t, 5>, 5> m_Board;
	std::array<std::array<bool, 5>, 5> m_Called;
};