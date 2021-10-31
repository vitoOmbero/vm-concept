#pragma once

#include <iostream>
#include <vector>
#include <string_view>


#include "Stack.h"
#include "FlagRegister.h"

using VMProgram = std::vector<int>;

#pragma  warning (disable : 26812)
enum InstructionCode
{
	_BEGIN_,

	OUT,	// Print registry value: OUT A;
	PSH,	// Push value into stack: PSH 42;
	SUM,	// Sum values in stack;
	POP,	// Pop value from the top of stack to registry A;
	SET,	// Set value into registry: SET A 10
	JMP,	// Skip next N instructions, where N is a parameter: JMP 125;
	CMP,	// Do signed substruction of the 2nd register value from the 1st one and set ZF and SF flags: CMP A B; 
	JNE,	// Do JMP N (jump if not equal), if zero equality flag  is FALSE (ZF == 0): JNE 25;
	JG,		// Do JMP N (jump if greater), if sign flag value in flags register (SF == 1): JG 87;
	ADD,	// Add value in registry B to value in registry A;
	HLT,	// stop execution;

	_END_
};


enum RegisterCode
{

	IP, // instuction pointer
	SP,	// stack pointer
	A,
	B,
	C,

	NREG
};

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


