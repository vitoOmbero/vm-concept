#pragma  warning (disable : 26812)
#include <string_view>
#include <array>

enum InstructionCode
{
	_BEGIN_, // NOTE: insert the string representation too!

	OUT = _BEGIN_,	// Print registry value: OUT A;
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
	A,	// nmaed registers
	B,
	C,

	NREG // not a register
};

static inline std::array<std::string_view, InstructionCode::_END_> g_instruction =
{
	"OUT",
	"PSH",	
	"SUM",	
	"POP",	
	"SET",	
	"JMP",	
	"CMP",	
	"JNE",	
	"JG",	
	"ADD",	
	"HLT",	
};

static inline std::array<std::string_view, RegisterCode::NREG> g_register =
{
	"IP",
	"SP",
	"A",
	"B",
	"C"
};

inline const std::string_view Str(InstructionCode ic)
{
	return g_instruction[ic];
};

inline const std::string_view Str(RegisterCode rc)
{
	return g_register[rc];
};

inline static const std::string_view kObjectFileHeader{ "VMC" };
inline static const int kNotIndex{ -1 };
template<int N> 
int64_t FindIndex(const std::array<std::string_view, N>& arr, const std::string_view& str)
{
	int index{ kNotIndex };
	auto it = std::find(arr.begin(), arr.end(), str);
	if (it != arr.end())
	{
		index = std::distance(arr.begin(), it);
	}
	return index;
};

/// <summary>
/// Detect if instruction is known
/// </summary>
/// <param name="str">token</param>
/// <returns>index in <see cref="g_instruction"/></returns>
inline int64_t FindInstruction(const std::string_view& str)
{
	return FindIndex(g_instruction, str);
}

inline int64_t FindRegister(const std::string_view& str)
{
	return FindIndex(g_register, str);
}

