#include "SnailNumber.h"

#include <stack>
#include <optional>
#include <cassert>

#include <iostream>

SnailNumber operator+(const SnailNumber& lhs, const SnailNumber& rhs)
{
	SnailNumber res;
	res.m_Value = std::make_shared<SnailNumber::SnailNumberVal>();
	res.m_Value->left = std::make_shared<SnailNumber::SnailNumberVariant>(lhs.m_Value);
	res.m_Value->right = std::make_shared<SnailNumber::SnailNumberVariant>(rhs.m_Value);

	res.Reduce();
	return res;
}

SnailNumber::SnailNumber(const std::string& val)
{
	ParseInputString(val);
}

std::uint64_t SnailNumber::GetMagnitude()
{
	return GetMagnitude(m_Value);
}

std::string SnailNumber::ToString()
{
	return ToString(m_Value);
}

void SnailNumber::Reduce()
{
	if (Explode())
	{
		Reduce();
	}
	else if (Split())
	{
		Reduce();
	}
}

bool SnailNumber::Explode()
{
	auto explodingPair = GetExplodingPair(m_Value, 1);

	if (explodingPair == nullptr)
	{
		return false;
	}

	assert(std::holds_alternative<pSnailNumberVal>(*explodingPair));
	assert(std::holds_alternative<int>(*std::get<pSnailNumberVal>(*explodingPair)->left));
	assert(std::holds_alternative<int>(*std::get<pSnailNumberVal>(*explodingPair)->right));

	pSnailNumberVariant leftCandidate;
	pSnailNumberVariant rightCandidate;

	bool leftFound = GetValueToLeft(explodingPair, leftCandidate, m_Value);
	bool rightFound = GetValueToRight(explodingPair, rightCandidate, m_Value);

	assert(leftFound);
	assert(rightFound);

	if (leftCandidate != nullptr)
	{
		assert(std::holds_alternative<int>(*leftCandidate));
		std::get<int>(*leftCandidate) += std::get<int>(*std::get<pSnailNumberVal>(*explodingPair)->left);
	}

	if (rightCandidate != nullptr)
	{
		assert(std::holds_alternative<int>(*rightCandidate));
		std::get<int>(*rightCandidate) += std::get<int>(*std::get<pSnailNumberVal>(*explodingPair)->right);
	}

	*explodingPair = 0;

	return true;
}

bool SnailNumber::Split()
{
	return Split(m_Value);
}

bool SnailNumber::Split(pSnailNumberVal val)
{
	if (std::holds_alternative<pSnailNumberVal>(*val->left))
	{
		if (Split(std::get<pSnailNumberVal>(*val->left)))
		{
			return true;
		}
	}
	else if (std::holds_alternative<int>(*val->left) && std::get<int>(*val->left) >= 10)
	{
		int currentVal = std::get<int>(*val->left);
		*val->left = std::make_shared<SnailNumberVal>(std::make_shared<SnailNumberVariant>(currentVal / 2), std::make_shared<SnailNumberVariant>((currentVal + 1) / 2));
		return true;
	}

	if (std::holds_alternative<pSnailNumberVal>(*val->right))
	{
		if (Split(std::get<pSnailNumberVal>(*val->right)))
		{
			return true;
		}
	}
	else if (std::holds_alternative<int>(*val->right) && std::get<int>(*val->right) >= 10)
	{
		int currentVal = std::get<int>(*val->right);
		*val->right = std::make_shared<SnailNumberVal>(std::make_shared<SnailNumberVariant>(currentVal / 2), std::make_shared<SnailNumberVariant>((currentVal + 1) / 2));
		return true;
	}

	return false;
}

SnailNumber::pSnailNumberVariant SnailNumber::GetExplodingPair(pSnailNumberVal val, int level)
{
	pSnailNumberVariant ret = nullptr;
	if (std::holds_alternative<pSnailNumberVal>(*val->left))
	{
		auto nextPair = val->left;
		if (level >= 4)
		{
			return nextPair;
		}
		ret = GetExplodingPair(std::get<pSnailNumberVal>(*nextPair), level + 1);

		if (ret != nullptr)
		{
			return ret;
		}
	}

	if (std::holds_alternative<pSnailNumberVal>(*val->right))
	{
		auto nextPair = val->right;
		if (level >= 4)
		{
			return nextPair;
		}
		ret = GetExplodingPair(std::get<pSnailNumberVal>(*nextPair), level + 1);

		if (ret != nullptr)
		{
			return ret;
		}
	}

	return nullptr;
}

bool SnailNumber::GetValueToLeft(const pSnailNumberVariant exploder, pSnailNumberVariant& leftCandidate, pSnailNumberVal val)
{
	if (std::holds_alternative<int>(*val->left))
	{
		leftCandidate = val->left;
	}
	else
	{
		if (val->left == exploder)
		{
			return true;
		}

		bool found = GetValueToLeft(exploder, leftCandidate, std::get<pSnailNumberVal>(*val->left));

		if (found)
		{
			return true;
		}
	}

	if (std::holds_alternative<int>(*val->right))
	{
		leftCandidate = val->right;
	}
	else
	{
		if (val->right == exploder)
		{
			return true;
		}

		bool found = GetValueToLeft(exploder, leftCandidate, std::get<pSnailNumberVal>(*val->right));

		if (found)
		{
			return true;
		}
	}

	return false;
}

bool SnailNumber::GetValueToRight(const pSnailNumberVariant exploder, pSnailNumberVariant& rightCandidate, pSnailNumberVal val)
{
	if (std::holds_alternative<int>(*val->right))
	{
		rightCandidate = val->right;
	}
	else
	{
		if (val->right == exploder)
		{
			return true;
		}

		bool found = GetValueToRight(exploder, rightCandidate, std::get<pSnailNumberVal>(*val->right));

		if (found)
		{
			return true;
		}
	}

	if (std::holds_alternative<int>(*val->left))
	{
		rightCandidate = val->left;
	}
	else
	{
		if (val->left == exploder)
		{
			return true;
		}

		bool found = GetValueToRight(exploder, rightCandidate, std::get<pSnailNumberVal>(*val->left));

		if (found)
		{
			return true;
		}
	}

	return false;
}

std::uint64_t SnailNumber::GetMagnitude(pSnailNumberVariant val)
{
	if (std::holds_alternative<int>(*val))
	{
		return std::get<int>(*val);
	}
	else
	{
		return GetMagnitude(std::get<pSnailNumberVal>(*val));
	}
}

std::uint64_t SnailNumber::GetMagnitude(pSnailNumberVal val)
{
	return 3 * GetMagnitude(val->left) + 2 * GetMagnitude(val->right);
}

std::string SnailNumber::ToString(pSnailNumberVariant val)
{
	if (std::holds_alternative<int>(*val))
	{
		return std::to_string(std::get<int>(*val));
	}
	else
	{
		return ToString(std::get<pSnailNumberVal>(*val));
	}
}

std::string SnailNumber::ToString(pSnailNumberVal val)
{
	return "[" + ToString(val->left) + "," + ToString(val->right) + "]";
}

void SnailNumber::ParseInputString(const std::string& val)
{
	std::stack<pSnailNumberVal> parsingStack;
	std::stack<bool> leftRightStack;
	for (char c : val)
	{
		if (c == '[')
		{
			auto nextVal = std::make_shared<SnailNumberVal>();
			if (!parsingStack.empty())
			{
				assert(!leftRightStack.empty());
				if (!leftRightStack.top())
				{
					parsingStack.top()->left = std::make_shared<SnailNumberVariant>(nextVal);
				}
				else
				{
					parsingStack.top()->right = std::make_shared<SnailNumberVariant>(nextVal);
				}
			}
			else
			{
				m_Value = nextVal;
			}

			leftRightStack.push(false);
			parsingStack.push(nextVal);
		}
		else if (c == ']')
		{
			parsingStack.pop();
			leftRightStack.pop();
		}
		else if (c == ',')
		{
			leftRightStack.top() = true;
		}
		else	//number
		{
			int nextVal = c - '0';
			if (!leftRightStack.top())
			{
				parsingStack.top()->left = std::make_shared<SnailNumberVariant>(nextVal);
			}
			else
			{
				parsingStack.top()->right = std::make_shared<SnailNumberVariant>(nextVal);
			}
		}
	}
}
