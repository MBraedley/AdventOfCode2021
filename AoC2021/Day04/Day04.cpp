// Day04.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "BingoBoard.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <sstream>

int main()
{
	std::filesystem::path input("input.txt");

	std::ifstream inStrm;
	inStrm.open(input);

	std::string balls;
	inStrm >> balls;

	std::vector<BingoBoard> boards;
	BingoBoard board;
	while (inStrm >> board)
	{
		boards.push_back(board);
	}
	
	std::stringstream sstrm(balls);
	char c;
	do
	{
		int ball;
		sstrm >> ball;
		for (auto& b : boards)
		{
			if (!b.IsWinner() && b.CallNumber(ball))
			{
				std::cout << "Score: " << (b.GetPartialScore() * ball) << std::endl;
			}
		}
	} while (sstrm >> c);
}
