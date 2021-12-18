#include "SnailNumber.h"

#include <stack>
#include <optional>
#include <cassert>

#include <iostream>

SnailNumber operator+(const SnailNumber& lhs, const SnailNumber& rhs)
{
	SnailNumber res;
	res.m_Value = std::make_shared<SnailNumber::SnailNumberVal>(lhs.m_Value, rhs.m_Value);

	std::cout << res.ToString() << std::endl;
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
	if (GetNestingDepth(m_Value) <= 4)
	{
		return false;
	}

	auto [left, var, right] = GetExplodingPair();

	assert(std::holds_alternative<pSnailNumberVal>(var.get()));
	auto pVal = std::get<pSnailNumberVal>(var.get());
	assert(std::holds_alternative<int>(pVal->left) && std::holds_alternative<int>(pVal->right));

	if (left.has_value())
	{
		left.value() += std::get<int>(pVal->left);
	}

	if (right.has_value())
	{
		right.value() += std::get<int>(pVal->right);
	}

	var.get() = 0;

	return true;
}

bool SnailNumber::Split()
{
	return Split(m_Value);
}

bool SnailNumber::Split(pSnailNumberVal val)
{
	if (std::holds_alternative<pSnailNumberVal>(val->left))
	{
		if (Split(std::get<pSnailNumberVal>(val->left)))
		{
			return true;
		}
	}
	else if (std::holds_alternative<int>(val->left) && std::get<int>(val->left) >= 10)
	{
		int currentVal = std::get<int>(val->left);
		val->left = std::make_shared<SnailNumberVal>(currentVal / 2, (currentVal + 1) / 2);
		return true;
	}
	
	if (std::holds_alternative<pSnailNumberVal>(val->right))
	{
		if (Split(std::get<pSnailNumberVal>(val->right)))
		{
			return true;
		}
	}
	else if (std::holds_alternative<int>(val->right) && std::get<int>(val->right) >= 10)
	{
		int currentVal = std::get<int>(val->right);
		val->right = std::make_shared<SnailNumberVal>(currentVal / 2, (currentVal + 1) / 2);
		return true;
	}

	return false;
}

std::uint32_t SnailNumber::GetNestingDepth(pSnailNumberVal val)
{
	std::uint32_t left = 1;
	if (std::holds_alternative<pSnailNumberVal>(val->left))
	{
		left += GetNestingDepth(std::get<pSnailNumberVal>(val->left));
	}

	std::uint32_t right = 1;
	if (std::holds_alternative<pSnailNumberVal>(val->right))
	{
		right += GetNestingDepth(std::get<pSnailNumberVal>(val->right));
	}

	return std::max(left, right);
}

SnailNumber::ExplodingPairVals SnailNumber::GetExplodingPair()
{
	std::cout << ToString() << std::endl;
	bool explodingPairFound = false;
	std::optional<std::reference_wrapper<int>> left;
	std::optional<std::reference_wrapper<int>> right;

	std::optional<std::reference_wrapper<SnailNumberVariant>> var;

	std::stack<pSnailNumberVal> searchingStack;
	std::stack<bool> leftRightStack;

	searchingStack.push(m_Value);
	leftRightStack.push(false);

	while (!explodingPairFound)
	{
		if (!leftRightStack.top())
		{
			if (std::holds_alternative<int>(searchingStack.top()->left))
			{
				left = std::get<int>(searchingStack.top()->left);
				leftRightStack.top() = true;
			}
			else if (searchingStack.size() >= 4)	//we've found our exploding pair
			{
				explodingPairFound = true;
				var = searchingStack.top()->left;
				leftRightStack.top() = true;
			}
			else
			{
				leftRightStack.top() = true;
				searchingStack.push(std::get<pSnailNumberVal>(searchingStack.top()->left));
				leftRightStack.push(false);
			}
		}
		else
		{
			if (std::holds_alternative<int>(searchingStack.top()->right))
			{
				left = std::get<int>(searchingStack.top()->right);

				while (leftRightStack.top())
				{
					leftRightStack.pop();
					searchingStack.pop();
				}

				leftRightStack.top() = true;
			}
			else if (searchingStack.size() >= 4)	//we've found our exploding pair
			{
				explodingPairFound = true;
				var = searchingStack.top()->right;
				//immediately pop the stacks to allow searching for the right side value
				leftRightStack.pop();
				searchingStack.pop();
			}
			else
			{
				searchingStack.push(std::get<pSnailNumberVal>(searchingStack.top()->right));
				leftRightStack.push(false);
			}
		}
	}

	while (!right.has_value() && !searchingStack.empty())
	{
		if (!leftRightStack.top())
		{
			if (std::holds_alternative<int>(searchingStack.top()->left))
			{
				right = std::get<int>(searchingStack.top()->left);
			}
			else
			{
				leftRightStack.push(false);
				searchingStack.push(std::get<pSnailNumberVal>(searchingStack.top()->left));
			}
		}
		else
		{
			if (std::holds_alternative<int>(searchingStack.top()->right))
			{
				right = std::get<int>(searchingStack.top()->right);
			}
			else
			{
				leftRightStack.pop();
				searchingStack.pop();
			}
		}
	}

	return std::make_tuple(left, var.value(), right);
}

std::uint64_t SnailNumber::GetMagnitude(SnailNumberVariant& val)
{
	if (std::holds_alternative<int>(val))
	{
		return std::get<int>(val);
	}
	else
	{
		return GetMagnitude(std::get<pSnailNumberVal>(val));
	}
}

std::uint64_t SnailNumber::GetMagnitude(pSnailNumberVal val)
{
	return 3 * GetMagnitude(val->left) + 2 * GetMagnitude(val->right);
}

std::string SnailNumber::ToString(SnailNumberVariant& val)
{
	if (std::holds_alternative<int>(val))
	{
		return std::to_string(std::get<int>(val));
	}
	else
	{
		return ToString(std::get<pSnailNumberVal>(val));
	}
}

std::string SnailNumber::ToString(pSnailNumberVal val)
{
	return "[" + ToString(val->left) + "," + ToString(val->right) +"]";
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
					parsingStack.top()->left = nextVal;
				}
				else
				{
					parsingStack.top()->right = nextVal;
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
				parsingStack.top()->left = nextVal;
			}
			else
			{
				parsingStack.top()->right = nextVal;
			}
		}
	}
}
