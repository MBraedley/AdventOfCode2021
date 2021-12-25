// Day24.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "ALU.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <queue>
#include <set>
#include <vector>
#include <array>
#include <limits>
#include <cassert>

int main()
{
	std::filesystem::path input("input.txt");

	std::ifstream inStrm;
	inStrm.open(input);

	std::vector<std::vector<std::string>> program;
	for (std::string line; std::getline(inStrm, line);)
	{
		if (line.starts_with("inp"))
		{
			program.push_back({});
		}
		program.back().push_back(line);
	}

	std::array<int, 14> coefficients = { 6, 9, 9, 1, 4, 1, 9, 9, 9, 1, 1, 1, 1, 1 };
	int i;

	auto testToMax = [&](int coeff) {
		std::int64_t minOutput = std::numeric_limits<std::int64_t>::max();
		for (int nc = 9; nc > 0; nc--)
		{
			ALU alu([&]() -> std::int64_t
				{
					if (i == coeff)
					{
						return nc;
					}
					return coefficients[i];
				});

			for (i = 0; i <= coeff; i++)
			{
				for (auto& inst : program[i])
				{
					alu.RunInstruction(inst);
				}
			}
			auto intermediateVal = alu.GetValue(ALU::RegisterName::z);
			if (intermediateVal < minOutput)
			{
				minOutput = intermediateVal;
				coefficients[coeff] = nc;

				std::cout << coeff << ": " << minOutput << " " << nc << std::endl;
			}
		}
	};

	testToMax(3);
	testToMax(5);
	testToMax(9);
	testToMax(10);
	testToMax(11);
	testToMax(12);
	testToMax(13);

	//Verify result
	auto inputFunc = [&]() -> std::int64_t
	{
		return coefficients[i];
	};

	ALU aluVeri1(inputFunc);
	for (i = 0; i < coefficients.size(); i++)
	{
		for (auto& inst : program[i])
		{
			aluVeri1.RunInstruction(inst);
		}
		std::cout << aluVeri1.GetValue(ALU::RegisterName::z) << std::endl;
	}

	assert(aluVeri1.GetValue(ALU::RegisterName::z) == 0);

	std::cout << "Part 1: ";
	for (int val : coefficients)
	{
		std::cout << val;
	}
	std::cout << std::endl;


	coefficients = { 1, 4, 9, 1, 1, 1, 7, 5, 3, 1, 1, 1, 1, 1 };
	auto testToMin = [&](int coeff) {
		std::int64_t minOutput = std::numeric_limits<std::int64_t>::max();
		for (int nc = 1; nc <= 9; nc++)
		{
			ALU alu([&]() -> std::int64_t
				{
					if (i == coeff)
					{
						return nc;
					}
					return coefficients[i];
				});

			for (i = 0; i <= coeff; i++)
			{
				for (auto& inst : program[i])
				{
					alu.RunInstruction(inst);
				}
			}
			auto intermediateVal = alu.GetValue(ALU::RegisterName::z);
			if (intermediateVal < minOutput)
			{
				minOutput = intermediateVal;
				coefficients[coeff] = nc;

			}
		}
	};
	
	//testToMin(0);
	//testToMin(1);
	//testToMin(2);
	testToMin(3);
	//testToMin(4);
	testToMin(5);
	//testToMin(6);
	//testToMin(7);
	//testToMin(8);
	testToMin(9);
	testToMin(10);
	testToMin(11);
	testToMin(12);
	testToMin(13);

	//Verify result
	ALU aluVeri2(inputFunc);
	for (i = 0; i < coefficients.size(); i++)
	{
		for (auto& inst : program[i])
		{
			aluVeri2.RunInstruction(inst);
		}
		std::cout << aluVeri2.GetValue(ALU::RegisterName::z) << std::endl;
	}

	//assert(aluVeri2.GetValue(ALU::RegisterName::z) == 0);

	std::cout << "Part 2: ";
	for (int val : coefficients)
	{
		std::cout << val;
	}
	std::cout << std::endl;
}
