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
	struct SnailNumberVal
	{
		SnailNumberVariant left;
		SnailNumberVariant right;
	};

	using ExplodingPairVals = std::tuple<std::optional<std::reference_wrapper<int>>, std::reference_wrapper<SnailNumberVariant>, std::optional<std::reference_wrapper<int>>>;

	void Reduce();
	bool Explode();
	bool Split();
	bool Split(pSnailNumberVal val);

	std::uint32_t GetNestingDepth(pSnailNumberVal val);
	ExplodingPairVals GetExplodingPair();

	std::uint64_t GetMagnitude(SnailNumberVariant& val);
	std::uint64_t GetMagnitude(pSnailNumberVal val);

	std::string ToString(SnailNumberVariant& val);
	std::string ToString(pSnailNumberVal val);

	void ParseInputString(const std::string& val);
	
	pSnailNumberVal m_Value;
};

