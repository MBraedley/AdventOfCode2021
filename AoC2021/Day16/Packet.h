#pragma once

#include <memory>
#include <bitset>
#include <vector>
#include <variant>
#include <deque>

class Packet;

struct BitLengthPayload
{
	const bool m_LengthType = false;	//Always 0;
	std::bitset<15> m_PayloadLength;
	std::vector<std::shared_ptr<Packet>> m_Payload;
};

struct PacketCountPayload
{
	const bool m_LengthType = true;	//Always 1;
	std::bitset<11> m_PayloadLength;
	std::vector<std::shared_ptr<Packet>> m_Payload;
};

struct LiteralVal
{
	bool m_MoreVals;
	std::bitset<4> m_ValPortion;
};

using PacketPayload = std::variant<
	std::vector<LiteralVal>,
	std::shared_ptr<BitLengthPayload>,
	std::shared_ptr<PacketCountPayload>
>;

class Packet : public std::enable_shared_from_this<Packet>
{
public:
	Packet(std::deque<bool>& dataStrm);

	std::uint32_t GetVerionSum();

private:
	std::bitset<3> m_Version;
	std::bitset<3> m_Type;
	PacketPayload m_Payload;
};

