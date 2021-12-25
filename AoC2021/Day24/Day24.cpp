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

	std::array<int, 14> testVal = { 1, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9, 9 };

	auto testFront = [&]()
	{
		for (int i = 9; i > 0; i--)
		{
			for (int j = 9; j > 0; j--)
			{
				std::size_t n = 0;
				ALU alu([&]() -> std::int64_t
					{
						if (n == 0)
						{
							return i;
						}

						if (n == 1)
						{
							return j;
						}

						return testVal[n];
					});

				for (n = 0; n < 3; n++)
				{
					for (auto& inst : program[n])
					{
						alu.RunInstruction(inst);
					}
				}

				if (alu.GetValue(ALU::RegisterName::z) == 0)
				{
					std::cout << "i: " << i << " j: " << j <<  std::endl;
								
					testVal[0] = i;
					testVal[1] = j;

					return;
				}
			}
		}
	};

	testFront();

	std::cout << std::endl;

	/*for (int i = 9; i > 0; i--)
	{
		for (int j = 9; j > 0; j--)
		{
			ALU alu([&]() -> std::int64_t
				{
					if (n == 3)
					{
						return i;
					}

					if (n == 4)
					{
						return j;
					}

					return testVal[n];
				});

			for (n = 0; n < 5; n++)
			{
				for (auto& inst : program[i])
				{
					alu.RunInstruction(inst);
				}
			}

			if (alu.GetValue(ALU::RegisterName::z) == 0)
			{
				std::cout << "i: " << i << " j: " << j << std::endl;
				if (i > testVal[3])
				{
					testVal[3] = i;
					testVal[4] = j;
				}
				else if (i == testVal[3])
				{
					if (j > testVal[4])
					{
						testVal[4] = j;
					}
				}
			}
		}
	}

	std::cout << std::endl;*/

	//for (int i = 9; i > 0; i--)
	//{
	//	for (int j = 9; j > 0; j--)
	//	{
	//		ALU alu([&]() -> std::int64_t
	//			{
	//				if (n == 5)
	//				{
	//					return i;
	//				}

	//				if (n == 6)
	//				{
	//					return j;
	//				}

	//				return testVal[n];
	//			});

	//		for (n = 0; n < 7; n++)
	//		{
	//			for (auto& inst : program[i])
	//			{
	//				alu.RunInstruction(inst);
	//			}
	//		}

	//		if (alu.GetValue(ALU::RegisterName::z) == 0)
	//		{
	//			std::cout << "i: " << i << " j: " << j << std::endl;
	//			if (i > testVal[5])
	//			{
	//				testVal[5] = i;
	//				testVal[6] = j;
	//			}
	//			else if (i == testVal[5])
	//			{
	//				if (j > testVal[6])
	//				{
	//					testVal[6] = j;
	//				}
	//			}
	//		}
	//	}
	//}

	std::vector<std::map<std::int64_t, int>> validN(14);
	std::set<std::int64_t> targetRange;
	targetRange.insert(0);

	std::array<std::int32_t, 14> zTops = { 10, 10, 100, 100, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 100, 50 };
	for (std::int32_t i = 13; i >= 2; i--)
	{
		std::set<std::int64_t> nextTargetRange;
		
		for (std::int64_t z = 0; z <= zTops[i]; z++)
		{
			for (std::int64_t n : {1, 2, 3, 4, 5, 6, 7, 8, 9})
			{
				ALU alu([n]() { return n; });
				alu.RunInstruction(ALU::Instruction::add, ALU::RegisterName::z, z);
				for (auto& inst : program[i])
				{
					alu.RunInstruction(inst);
				}

				auto zVal = alu.GetValue(ALU::RegisterName::z);
				if (targetRange.contains(zVal))
				{
					nextTargetRange.insert(z);

					validN[i].emplace(z, n);
				}
			}
		}
		std::cout << "Index: " << i << " z-range: " << *nextTargetRange.begin() << " " << *nextTargetRange.rbegin() << std::endl;
		std::swap(targetRange, nextTargetRange);

		std::cout << std::endl;
	}

	////Verify result
	////testVal = { 9, 9, 9, 9, 4, 9, 9, 9, 9, 9, 9, 9, 9, 9 };
	std::size_t i = 0;
	std::int64_t lastZ = 0;
	auto inputFunc = [&]() -> std::int64_t
	{
		if (!validN[i].empty())
		{
			assert(validN[i].contains(lastZ));
			return validN[i][lastZ];
		}

		return testVal[i];
	};

	ALU aluVeri(inputFunc);
	for (i = 0; i < testVal.size(); i++)
	{
		for (auto& inst : program[i])
		{
			aluVeri.RunInstruction(inst);
		}
		lastZ = aluVeri.GetValue(ALU::RegisterName::z);
	}

	assert(aluVeri.GetValue(ALU::RegisterName::z) == 0);

	std::cout << "Part 1: ";
	for (int val : testVal)
	{
		std::cout << val;
	}
	std::cout << std::endl;


	//std::cout << "Part 2: " << count << std::endl;
}
