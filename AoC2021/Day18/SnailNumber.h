#pragma once
#include <variant>
#include <memory>
#include <string>
#include <optional>

class SnailNumber
{
public:
	friend SnailNumber operator+(const SnailNumber& lhs, const SnailNumber& rhs);

	SnailNumber() = default;
	SnailNumber(const std::string& val);

	~SnailNumber() = default;

	std::uint64_t GetMagnitude();

	std::string ToString();

private:
	struct SnailNumberVal;
	using pSnailNumberVal = std::shared_ptr<SnailNumberVal>;
	using SnailNumberVariant = std::variant<int, pSnailNumberVal>;
	using pSnailNumberVariant = std::shared_ptr<SnailNumberVariant>;
	struct SnailNumberVal
	{
		pSnailNumberVariant left;
		pSnailNumberVariant right;
	};

	void Reduce();
	bool Explode();
	bool Split();
	bool Split(pSnailNumberVal val);

	pSnailNumberVariant GetExplodingPair(pSnailNumberVal val, int level);
	bool GetValueToLeft(const pSnailNumberVariant exploder, pSnailNumberVariant& leftCandidate, pSnailNumberVal val);
	bool GetValueToRight(const pSnailNumberVariant exploder, pSnailNumberVariant& rightCandidate, pSnailNumberVal val);

	std::uint64_t GetMagnitude(pSnailNumberVariant val);
	std::uint64_t GetMagnitude(pSnailNumberVal val);

	std::string ToString(pSnailNumberVariant val);
	std::string ToString(pSnailNumberVal val);

	void ParseInputString(const std::string& val);
	
	pSnailNumberVal m_Value;
};

