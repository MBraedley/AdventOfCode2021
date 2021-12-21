#pragma once
#include <unordered_map>
#include <string>

class GameState
{
public:
	GameState() = default;
	~GameState() = default;

	GameState(const GameState& other) = default;
	GameState& operator=(const GameState& other) = default;

	std::unordered_map<GameState, std::uint64_t> RollPlayer1() const;
	std::unordered_map<GameState, std::uint64_t> RollPlayer2() const;

	bool HasPlayer1Won() const { return m_P1Score >= 21; }
	bool HasPlayer2Won() const { return m_P2Score >= 21; }

	std::string ToString() const;

	friend bool operator==(const GameState& lhs, const GameState& rhs);

private:
	GameState RollP1(std::uint16_t diceTotal) const;
	GameState RollP2(std::uint16_t diceTotal) const;

	std::uint16_t m_P1Pos = 9;
	std::uint16_t m_P2Pos = 4;
	std::uint16_t m_P1Score = 0;
	std::uint16_t m_P2Score = 0;
};

template<>
struct std::hash<GameState>
{
	std::size_t operator()(GameState const& gs) const noexcept
	{
		return std::hash<std::string>{}(gs.ToString());
	}
};
