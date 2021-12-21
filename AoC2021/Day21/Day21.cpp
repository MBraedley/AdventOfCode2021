// Day21.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "GameState.h"

#include <iostream>
#include <unordered_map>
#include <vector>

class DeterministicDice
{
public:
	DeterministicDice() = default;

	std::uint16_t GetRollTotal()
	{
		std::uint16_t result = (m_NextValue + 1) * 3;
		if (m_NextValue == 100)
		{
			result -= 200;
		}
		if (m_NextValue == 99)
		{
			result -= 100;
		}

		m_NextValue += 3;
		if (m_NextValue > 100)
		{
			m_NextValue -= 100;
		}

		return result;
	}

private:
	std::uint16_t m_NextValue = 1;
};

int main()
{
	std::uint16_t player1Pos = 9;
	std::uint16_t player2Pos = 4;

	std::uint16_t player1Score = 0;
	std::uint16_t player2Score = 0;

	DeterministicDice die;

	std::uint16_t dieRollCount = 0;

	while (true)
	{
		player1Pos += die.GetRollTotal() % 10;
		if (player1Pos > 10)
		{
			player1Pos -= 10;
		}
		player1Score += player1Pos;

		dieRollCount += 3;

		if (player1Score >= 1000)
		{
			break;
		}

		player2Pos += die.GetRollTotal() % 10;
		if (player2Pos > 10)
		{
			player2Pos -= 10;
		}
		player2Score += player2Pos;

		dieRollCount += 3;

		if (player2Score >= 1000)
		{
			break;
		}
	}

	std::cout << "Part 1: " << std::min(player1Score, player2Score) * dieRollCount << std::endl;

	std::unordered_map<GameState, std::uint64_t> activeStates;
	activeStates.emplace(GameState(), 1);
	std::uint64_t p1Wins = 0;
	std::uint64_t p2Wins = 0;

	while (!activeStates.empty())
	{
		std::unordered_map<GameState, std::uint64_t> nextStates;
		for (const auto& [gs, count] : activeStates)
		{
			for (const auto& [ngs, ncount] : gs.RollPlayer1())
			{
				if (ngs.HasPlayer1Won())
				{
					p1Wins += count * ncount;
				}
				else
				{
					nextStates[ngs] += count * ncount;
				}
			}
		}

		std::swap(activeStates, nextStates);
		nextStates.clear();

		for (const auto& [gs, count] : activeStates)
		{
			for (const auto& [ngs, ncount] : gs.RollPlayer2())
			{
				if (ngs.HasPlayer2Won())
				{
					p2Wins += count * ncount;
				}
				else
				{
					nextStates[ngs] += count * ncount;
				}
			}
		}
		std::swap(activeStates, nextStates);
	}

	std::cout << "Part 2: " << std::max(p1Wins, p2Wins) << std::endl;
}
