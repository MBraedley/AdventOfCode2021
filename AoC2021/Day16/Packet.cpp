#include "Packet.h"

Packet::Packet(std::deque<bool>& dataStrm)
{
	m_Version[2] = dataStrm.front();
	dataStrm.pop_front();
	m_Version[1] = dataStrm.front();
	dataStrm.pop_front();
	m_Version[0] = dataStrm.front();
	dataStrm.pop_front();

	m_Type[2] = dataStrm.front();
	dataStrm.pop_front();
	m_Type[1] = dataStrm.front();
	dataStrm.pop_front();
	m_Type[0] = dataStrm.front();
	dataStrm.pop_front();

	if (m_Type.to_ulong() == 4)	// literal values
	{
		std::vector<LiteralVal> payload;
		bool moreVals = true;
		while (moreVals)
		{
			LiteralVal litVal;
			litVal.m_MoreVals = dataStrm.front();
			dataStrm.pop_front();

			litVal.m_ValPortion[3] = dataStrm.front();
			dataStrm.pop_front();
			litVal.m_ValPortion[2] = dataStrm.front();
			dataStrm.pop_front();
			litVal.m_ValPortion[1] = dataStrm.front();
			dataStrm.pop_front();
			litVal.m_ValPortion[0] = dataStrm.front();
			dataStrm.pop_front();

			payload.push_back(litVal);
			moreVals = litVal.m_MoreVals;
		}

		m_Payload = payload;
	}
	else
	{
		bool opType = dataStrm.front();
		dataStrm.pop_front();
		if (opType)	//packet count
		{
			PacketCountPayload payload;
			for (std::size_t i = 0; i < payload.m_PayloadLength.size(); i++)
			{
				payload.m_PayloadLength <<= 1;
				payload.m_PayloadLength[0] = dataStrm.front();
				dataStrm.pop_front();
			}

			for (std::size_t i = 0; i < payload.m_PayloadLength.to_ulong(); i++)
			{
				payload.m_Payload.push_back(std::make_shared<Packet>(dataStrm));
			}

			m_Payload = std::make_shared<PacketCountPayload>(payload);
		}
		else
		{
			BitLengthPayload payload;
			for (std::size_t i = 0; i < payload.m_PayloadLength.size(); i++)
			{
				payload.m_PayloadLength <<= 1;
				payload.m_PayloadLength[0] = dataStrm.front();
				dataStrm.pop_front();
			}

			auto bitLength = payload.m_PayloadLength.to_ulong();
			std::deque<bool> plStrm;
			plStrm.assign(dataStrm.cbegin(), dataStrm.cbegin() + bitLength);
			dataStrm.erase(dataStrm.cbegin(), dataStrm.cbegin() + bitLength);

			while (!plStrm.empty())
			{
				payload.m_Payload.push_back(std::make_shared<Packet>(plStrm));
			}

			m_Payload = std::make_shared<BitLengthPayload>(payload);
		}
	}
}

std::uint32_t Packet::GetVerionSum()
{
	std::uint32_t ret = m_Version.to_ulong();

	std::vector<std::shared_ptr<Packet>> payloadPackets;
	if (std::holds_alternative<std::shared_ptr<BitLengthPayload>>(m_Payload))
	{
		payloadPackets = std::get<std::shared_ptr<BitLengthPayload>>(m_Payload)->m_Payload;
	}
	else if (std::holds_alternative<std::shared_ptr<PacketCountPayload>>(m_Payload))
	{
		payloadPackets = std::get<std::shared_ptr<PacketCountPayload>>(m_Payload)->m_Payload;
	}

	for (auto& packet : payloadPackets)
	{
		ret += packet->GetVerionSum();
	}

	return ret;
}
