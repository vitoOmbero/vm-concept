#include "Vmc.h"

#include <fstream>

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


int main(int argc, char** argv)
{
	argc--;
	argv++;

	if (argc < 1)
	{
		std::cout << "Only one argument is supported - the filename (object file) e.g. \"my_src.obj\"" << std::endl;
	}
	
	std::ifstream is(argv[0], std::ios::in | std::ios::binary);

	if (!is) {
		std::cerr << "Some problems have acquired when opening the file. Does file exist? ";
		std::cerr << argv[0];
		return EXIT_FAILURE;
	};

	if (!is.is_open()) {
		std::cerr << "Bad filename for .obj file " << argv[0] << std::endl;
		return EXIT_FAILURE;
	}

	VirtualMachine vmc;
	if (argc < 1 && false) {
		vmc.Run(test_program_03);
	}
	else
	{
		char header[4]; header[3] = '\0';
		is.read(header, 3);
		if (strcmp(header, kObjectFileHeader.data()) != 0)
		{
			is.close();
			std::cerr << "Bad object file " << argv[0] << std::endl;
			return EXIT_FAILURE;
		}

		VMProgram loaded;
		int64_t word;
		while (is.read(reinterpret_cast<char*>(&word), 8))
		{
			loaded.push_back(word);
		}
		is.close();

		vmc.Run(loaded);
	}

	return EXIT_SUCCESS;
}