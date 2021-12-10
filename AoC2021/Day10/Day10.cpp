// Day10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <stack>
#include <chrono>
#include <cassert>

bool Opens(char c)
{
	return c == '(' || c == '[' || c == '{' || c == '<';
}

bool Matches(char opener, char closer)
{
	switch (opener)
	{
	case '(':
		return closer == ')';
	case '[':
		return closer == ']';
	case '{':
		return closer == '}';
	case '<':
		return closer == '>';
	default:
		return false;
	}
}

int main()
{
	std::filesystem::path input("input.txt");

	std::ifstream inStrm;
	inStrm.open(input);

	std::vector<std::string> values;
	std::string val;
	while (inStrm >> val)
	{
		values.push_back(val);
	}

	auto startTS = std::chrono::high_resolution_clock::now();

	std::uint64_t score = 0;
	constexpr std::uint32_t paren = 3;
	constexpr std::uint32_t bracket = 57;
	constexpr std::uint32_t brace = 1197;
	constexpr std::uint32_t angle = 25137;

	std::vector<std::stack<char>> incompleteLines;

	for (std::string& line : values)
	{
		std::stack<char> chunkStack;
		bool error = false;
		for (char c : line)
		{
			if (Opens(c))
			{
				chunkStack.push(c);
			}
			else
			{
				assert(chunkStack.size() != 0);
				char opener = chunkStack.top();
				if (!Matches(opener, c))
				{
					error = true;

					switch (c)
					{
					case ')':
						score += paren;
						break;
					case ']':
						score += bracket;
						break;
					case '}':
						score += brace;
						break;
					case '>':
						score += angle;
						break;
					default:
						assert(false);
						break;
					}

					break;
				}
				else
				{
					chunkStack.pop();
				}
			}
		}

		if (!error)
		{
			incompleteLines.push_back(chunkStack);
		}
	}

	std::cout << "Part 1: " << score << std::endl;

	std::vector<std::uint64_t> scores;
	scores.reserve(incompleteLines.size());

	for (auto& line : incompleteLines)
	{
		score = 0;
		while (!line.empty())
		{
			score *= 5;
			switch (line.top())
			{
			case '(':
				score += 1;
				break;
			case '[':
				score += 2;
				break;
			case '{':
				score += 3;
				break;
			case '<':
				score += 4;
				break;
			default:
				assert(false);
				break;
			}
			line.pop();
		}
		scores.push_back(score);
	}

	assert(scores.size() % 2 == 1);
	std::sort(scores.begin(), scores.end());
	score = scores[scores.size() / 2];
	std::cout << "Part 2: " << score << std::endl;

	auto stopTS = std::chrono::high_resolution_clock::now();

	std::cout << "Time: " << std::chrono::duration<double, std::milli>( stopTS - startTS) << std::endl;
}
