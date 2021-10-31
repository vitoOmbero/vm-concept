#include "Vmc.h"

const VMProgram test_program_01 = {
	PSH, 5,
	PSH, 6,
	SUM,
	POP,
	OUT, A,
	HLT
};

const VMProgram test_program_02 = {
	SET, A, 10,
	SET, B, 15,
	SET, C, 17,
	OUT, A,
	OUT, B,
	OUT, C,
	ADD,
	OUT, A,
	HLT
};

const VMProgram test_program_03 = {
	JMP, 15,

	SET, A, 0,
	SET, B, 0,
	SET, C, 0,
	OUT, A,
	OUT, B,
	OUT, C,

	SET, A, 45,
	SET, B, -3,
	SET, C, -1,
	CMP, C, B,

	JNE, 1,
	HLT,

	CMP, A, C,
	JG, 1,
	HLT,

	ADD,
	OUT, A,
	HLT
};

int main()
{
	VirtualMachine vmc;
	vmc.Run(test_program_03);

	return EXIT_SUCCESS;
}