// Day17.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include <map>
#include <set>
#include <regex>
#include <cassert>

std::uint64_t TriangularNumber(std::uint32_t n)
{
	return (n * (static_cast<std::uint64_t>(n) + 1)) / 2;
}

class TargetArea
{
public:
	TargetArea(int xMin, int xMax, int yMin, int yMax) :
		m_XMin(xMin),
		m_XMax(xMax),
		m_YMin(yMin),
		m_YMax(yMax)
	{}

	~TargetArea() = default;

	bool TestXVelocity(int xVel)
	{
		int xPos = 0;
		while (true)
		{
			xPos += xVel;

			if (xVel > 0)
			{
				xVel--;
			}
			if (xVel < 0)
			{
				xVel++;
			}

			if (xPos >= m_XMin && xPos <= m_XMax)
			{
				return true;
			}

			if (xPos > m_XMax)	//Gone too far
			{
				return false;
			}

			if (xPos < m_XMin && xVel == 0)	//Haven't gone far enough
			{
				return false;
			}
		}
		return false;	//make the compiler happy
	}

	bool TestXYVelocity(int xVel, int yVel)
	{
		int xPos = 0;
		int yPos = 0;
		while (yPos > m_YMin && xPos <= m_XMax)
		{
			xPos += xVel;
			yPos += yVel;

			if (xVel > 0)
			{
				xVel--;
			}
			if (xVel < 0)
			{
				xVel++;
			}

			yVel--;

			if (xPos >= m_XMin && xPos <= m_XMax && yPos >= m_YMin && yPos <= m_YMax)
			{
				return true;
			}
		}
		return false;
	}

private:
	int m_XMin;
	int m_XMax;
	int m_YMin;
	int m_YMax;
};

int main()
{
	std::filesystem::path input("input.txt");

	std::ifstream inStrm;
	inStrm.open(input);

	std::string inLine;
	std::getline(inStrm, inLine);

	std::regex targetR("x=(-?[0-9]+)\\.\\.(-?[0-9]+), y=(-?[0-9]+)\\.\\.(-?[0-9]+)");
	std::smatch m;
	bool found = std::regex_search(inLine, m, targetR);
	assert(found);

	int xMin = std::min(std::stoi(m[1]), std::stoi(m[2]));
	int xMax = std::max(std::stoi(m[1]), std::stoi(m[2]));

	int yMin = std::min(std::stoi(m[3]), std::stoi(m[4]));
	int yMax = std::max(std::stoi(m[3]), std::stoi(m[4]));

	int yIVel = -yMin - 1;

	int yHeight = TriangularNumber(yIVel);

	std::cout << "Part 1: " << yHeight << std::endl;

	std::uint32_t count = 0;
	TargetArea tgt(xMin, xMax, yMin, yMax);

	for (int xVel = 1; xVel <= xMax; xVel++)
	{
		if (tgt.TestXVelocity(xVel))
		{
			for (int yVel = yMin; yVel <= yIVel; yVel++)
			{
				if (tgt.TestXYVelocity(xVel, yVel))
				{
					count++;
				}
			}
		}
	}

	std::cout << "Part 2: " << count << std::endl;
}
