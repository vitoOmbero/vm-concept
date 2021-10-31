#pragma once

#include <iostream>
#include <vector>
#include <string_view>

#include "identifiers.h"
#include "Stack.h"
#include "FlagRegister.h"

using VMProgram = std::vector<int64_t>;

class VirtualMachine
{
public:
	using ValueType = int64_t;

	VirtualMachine(bool traceModeOn = true);

	void Run(const VMProgram& program);

private:
	ValueType m_register[NREG];
	bool m_traceMode;
	bool m_isRunning;
	FlagRegister m_flags;
	Stack m_stack;
	const VMProgram* m_program;

private:
	void Show(const std::string_view& text);
	void Show(ValueType val);
	void Show(InstructionCode opCode, const ValueType* val = nullptr);
	void Show(InstructionCode opCode, RegisterCode regCode, const ValueType* val = nullptr);
	void Show(InstructionCode opCode, RegisterCode regCode, RegisterCode regCode2);


	ValueType Fetch();
	void Evaluate(ValueType code);
	RegisterCode RegisterName(ValueType code);
	void Skip(ValueType n);
};


