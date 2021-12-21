#include "GameState.h"

#include <sstream>

std::unordered_map<GameState, std::uint64_t> GameState::RollPlayer1() const
{
	std::unordered_map<GameState, std::uint64_t> nextStates;
	nextStates.emplace(RollP1(3), 1);
	nextStates.emplace(RollP1(4), 3);
	nextStates.emplace(RollP1(5), 6);
	nextStates.emplace(RollP1(6), 7);
	nextStates.emplace(RollP1(7), 6);
	nextStates.emplace(RollP1(8), 3);
	nextStates.emplace(RollP1(9), 1);

	return nextStates;
}

std::unordered_map<GameState, std::uint64_t> GameState::RollPlayer2() const
{
	std::unordered_map<GameState, std::uint64_t> nextStates;
	nextStates.emplace(RollP2(3), 1);
	nextStates.emplace(RollP2(4), 3);
	nextStates.emplace(RollP2(5), 6);
	nextStates.emplace(RollP2(6), 7);
	nextStates.emplace(RollP2(7), 6);
	nextStates.emplace(RollP2(8), 3);
	nextStates.emplace(RollP2(9), 1);

	return nextStates;
}

std::string GameState::ToString() const
{
	std::stringstream sstrm;
	sstrm << m_P1Pos << "-" << m_P1Score << "-" << m_P2Pos << "-" << m_P2Score;
	return sstrm.str();
}

GameState GameState::RollP1(std::uint16_t diceTotal) const
{
	GameState next(*this);
	next.m_P1Pos += diceTotal;
	if (next.m_P1Pos > 10)
	{
		next.m_P1Pos -= 10;
	}

	next.m_P1Score += next.m_P1Pos;
	return next;
}

GameState GameState::RollP2(std::uint16_t diceTotal) const
{
	GameState next(*this);
	next.m_P2Pos += diceTotal;
	if (next.m_P2Pos > 10)
	{
		next.m_P2Pos -= 10;
	}

	next.m_P2Score += next.m_P2Pos;
	return next;
}

bool operator==(const GameState& lhs, const GameState& rhs)
{
	return lhs.m_P1Pos == rhs.m_P1Pos
		&& lhs.m_P2Pos == rhs.m_P2Pos
		&& lhs.m_P1Score == rhs.m_P1Score
		&& lhs.m_P2Score == rhs.m_P2Score;
}
