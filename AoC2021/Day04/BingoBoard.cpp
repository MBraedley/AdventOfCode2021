#include "BingoBoard.h"

bool BingoBoard::CallNumber(std::uint16_t num)
{
	for (std::size_t row = 0; row < 5; row++)
	{
		for (std::size_t col = 0; col < 5; col++)
		{
			if (m_Board[row][col] == num)
			{
				m_Called[row][col] = true;
			}
		}
	}

	return IsWinner();
}

bool BingoBoard::IsWinner()
{
	for (std::size_t i = 0; i < 5; i++)
	{
		bool rowCheck = true;
		bool colCheck = true;
		for (std::size_t j = 0; j < 5; j++)
		{
			rowCheck = rowCheck && m_Called[i][j];
			colCheck = colCheck && m_Called[j][i];
		}

		if (rowCheck || colCheck)
		{
			return true;
		}
	}

	return false;
}

std::uint32_t BingoBoard::GetPartialScore()
{
	std::uint32_t score = 0;
	for (std::size_t row = 0; row < 5; row++)
	{
		for (std::size_t col = 0; col < 5; col++)
		{
			if (!m_Called[row][col])
			{
				score += m_Board[row][col];
			}
		}
	}
	return score;
}

std::istream& operator>>(std::istream& in, BingoBoard& board)
{
	for (std::size_t row = 0; row < 5; row++)
	{
		for (std::size_t col = 0; col < 5; col++)
		{
			int val;
			in >> val;
			board.m_Board[row][col] = val;
			board.m_Called[row][col] = false;
		}
	}

	return in;
}

std::ostream& operator<<(std::ostream& out, BingoBoard& board)
{
	for (std::size_t row = 0; row < 5; row++)
	{
		for (std::size_t col = 0; col < 5; col++)
		{
			out.width(2);
			out << std::right << static_cast<int>(board.m_Board[row][col]);
			out << (board.m_Called[row][col] ? "*" : " ") << " ";
		}
		out << std::endl;
	}

	return out;
}
