#include "ALU.h"

#include <sstream>
#include <cassert>

void ALU::RunInstruction(std::string inst)
{
	std::stringstream sstrm(inst);
	std::string instName, regA;
	sstrm >> instName >> regA;

	if (InstructionNames.at(instName) == Instruction::inp)
	{
		RunInstruction(Instruction::inp, RegisterName(regA[0]), m_InputCallback());
		return;
	}

	std::string regB;
	sstrm >> regB;
	if (regB == "w" || regB == "x" || regB == "y" || regB == "z")
	{
		RunInstruction(InstructionNames.at(instName), RegisterName(regA[0]), RegisterName(regB[0]));
	}
	else
	{
		RunInstruction(InstructionNames.at(instName), RegisterName(regA[0]), std::stoll(regB));
	}
}

void ALU::RunInstruction(Instruction inst, RegisterName reg, std::int64_t value)
{
	std::int64_t& regA = m_Registers[reg];
	switch (inst)
	{
	case ALU::Instruction::inp:
		regA = value;
		break;
	case ALU::Instruction::add:
		regA += value;
		break;
	case ALU::Instruction::mul:
		regA *= value;
		break;
	case ALU::Instruction::div:
		assert(value != 0);
		regA /= value;
		break;
	case ALU::Instruction::mod:
		assert(value > 0);
		assert(regA >= 0);
		regA %= value;
		break;
	case ALU::Instruction::eql:
		regA = (regA == value ? 1 : 0);
		break;
	default:
		assert(false);
		break;
	}
}

void ALU::RunInstruction(Instruction inst, RegisterName regA, RegisterName regB)
{
	assert(inst != Instruction::inp);
	RunInstruction(inst, regA, m_Registers[regB]);
}

std::int64_t ALU::GetValue(RegisterName reg)
{
	return m_Registers[reg];
}
