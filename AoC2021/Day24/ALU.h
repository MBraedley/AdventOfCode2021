#pragma once

#include <map>
#include <string>
#include <functional>

class ALU
{
public:
	enum class Instruction
	{
		inp,
		add,
		mul,
		div,
		mod,
		eql,
	};

	enum class RegisterName : char
	{
		w = 'w',
		x,
		y,
		z,
	};

	explicit ALU(std::function<std::int64_t(void)> inputCallback) :
		m_InputCallback(inputCallback)
	{}

	void RunInstruction(std::string inst);
	void RunInstruction(Instruction inst, RegisterName reg, std::int64_t value);
	void RunInstruction(Instruction inst, RegisterName regA, RegisterName regB);

	std::int64_t GetValue(RegisterName reg);

	inline static const std::map<std::string, Instruction> InstructionNames
	{
		{"inp", Instruction::inp},
		{"add", Instruction::add},
		{"mul", Instruction::mul},
		{"div", Instruction::div},
		{"mod", Instruction::mod},
		{"eql", Instruction::eql},
	};

private:
	std::map<RegisterName, std::int64_t> m_Registers
	{
		{RegisterName::w, 0},
		{RegisterName::x, 0},
		{RegisterName::y, 0},
		{RegisterName::z, 0},
	};

	std::function<std::int64_t(void)> m_InputCallback;
};

