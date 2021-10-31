#include "Vmc.h"

const std::string_view OpCodeStr(InstructionCode ic)
{
	switch (ic)
	{
	case JG:
		return { "JG" };
	case JNE:
		return { "JNE" };
	case CMP:
		return { "CMP" };
	case JMP:
		return { "JMP" };
	case ADD:
		return { "ADD" };
	case OUT:
		return { "OUT" };
	case PSH:
		return { "PSH" };
	case SUM:
		return { "SUM" };
	case POP:
		return { "POP" };
	case SET:
		return { "SET" };
	case HLT:
		return { "HLT" };
	default:
		return { "Undocumentated Instruction Code" };
	}
};

const std::string_view RegCodeStr(RegisterCode rc)
{
	switch (rc)
	{
	case IP:
		return { "IP" };
	case SP:
		return { "SP" };
	case A:
		return { "A" };
	case B:
		return { "B" };
	case C:
		return { "C" };
	case NREG:
		return { "NREG" };
	default:
		return { "Undocumentated Register Code" };
	}
}

void VirtualMachine::Show(const std::string_view& text)
{
	if (!m_traceMode){
		return;
	}
	std::cout << "VM| " << text << std::endl;
};

void VirtualMachine::Show(ValueType val)
{
	if (!m_traceMode) {
		return;
	}
	std::cout << "VM| Value: " << val << std::endl;
};

void VirtualMachine::Show(InstructionCode opCode, const ValueType* val)
{
	if (!m_traceMode) {
		return;
	}
	if (val == nullptr)
	{
		std::cout << "VM| OpCode: " << OpCodeStr(opCode) << std::endl;
	}
	else
	{
		std::cout << "VM| OpCode: " << OpCodeStr(opCode) << " Param:" << *val << std::endl;
	}
}
void VirtualMachine::Show(InstructionCode opCode, RegisterCode regCode, const ValueType* val)
{
	if (!m_traceMode) {
		return;
	}
	if (val == nullptr)
	{
		std::cout << "VM| OpCode: " << OpCodeStr(opCode) << " Register: " << RegCodeStr(regCode) << std::endl;
	}
	else
	{
		std::cout << "VM| OpCode: " << OpCodeStr(opCode) << " Register: " << RegCodeStr(regCode) << " Param:" << *val << std::endl;
	}
}
void VirtualMachine::Show(InstructionCode opCode, RegisterCode regCode, RegisterCode regCode2)
{
	std::cout << "VM| OpCode: " << OpCodeStr(opCode) << " Register: " << RegCodeStr(regCode) << " Register2: " << RegCodeStr(regCode2) << std::endl;
}

VirtualMachine::VirtualMachine(bool traceModeOn): 
	m_traceMode(traceModeOn), 
	m_isRunning(false),
	m_flags(),
	m_stack(m_register[SP]),
	m_program(nullptr)
{
	m_register[IP] = 0;
}

VirtualMachine::ValueType VirtualMachine::Fetch()
{
	return (*m_program)[m_register[IP]];
};

void VirtualMachine::Run(const VMProgram& program)
{
	std::cout << "VM: is running..." << std::endl;
	std::cout << "VM| Execution: test_program_01" << std::endl;

	m_isRunning = true;
	m_program = &program;

	while (m_isRunning)
	{
		auto code = Fetch();
		Evaluate(code);
	}

	std::cout << "VM: shutdown." << std::endl;
}

void VirtualMachine::Evaluate(ValueType code)
{

	if ((code > static_cast<int>(_END_)) ||
		(code < static_cast<int>(_BEGIN_))) {
		++m_register[IP];
		return;
	}
	auto ic = static_cast<InstructionCode>(code);

	switch (ic)
	{
	case CMP:
		{
		++m_register[IP];
		auto regCode = Fetch();
		auto regLeft = RegisterName(regCode);
		if (regLeft == RegisterCode::NREG) {
			++m_register[IP];
			break;
		}
		++m_register[IP];
		regCode = Fetch();
		auto regRight = RegisterName(regCode);
		if (regRight == RegisterCode::NREG) {
			break;
		}
		Show(CMP, regLeft, regRight);
		auto res = m_register[regLeft] - m_register[regRight];
		m_flags.SetZF(res == 0);
		m_flags.SetSF(res < 0);
		}
		break;
	case JNE:
		{
			++m_register[IP];
			auto val = Fetch();
			Show(JNE, &val);
			if (!m_flags.GetZF()) {
				Skip(val);
			}
		}
		break;
	case JG:
	{
		++m_register[IP];
		auto val = Fetch();
		Show(JG, &val);
		if (!m_flags.GetSF()) {
			Skip(val);
		}
	}
	break;
	case JMP:
		{
			++m_register[IP];
			auto val = Fetch();
			Show(JMP, &val);
			Skip(val);
		}
		break;
	case ADD:
		Show(ADD);
		m_register[A] += m_register[B];
		break;
	case OUT:
		{
			++m_register[IP];
			auto regCode = Fetch();
			auto reg = RegisterName(regCode);
			if (reg == RegisterCode::NREG) {
				break;
			}
			Show(OUT, reg);
	#pragma warning (disable : 6385)
			Show(m_register[reg]);

			if (!m_traceMode) {
				std::cout << m_register[reg];
			}
		}
		break;
	case PSH:
		++m_register[IP];
		m_stack.Push(Fetch());
		Show(PSH, m_stack.Top());
		break;
	case SUM:
		Show(SUM);
		{
			Stack::ValueType sum{ 0 };
			while (m_stack.Peek() != Stack::kNotAValue)
			{
				auto v = m_stack.Pop();
				if (v != Stack::kNotAValue) {
					sum += v;
				}
			}
			m_stack.Push(sum);
		}
		break;
	case POP:
		Show(POP);
		m_register[A] = m_stack.Pop();
		break;
	case SET:
		{
			++m_register[IP];
			auto regCode = Fetch();
			auto reg = RegisterName(regCode);
			if (reg == RegisterCode::NREG)
			{
				++m_register[IP];
				++m_register[IP];
				return;
			}
			++m_register[IP];
			auto val = Fetch();
			Show(SET, reg, &val);
			
			m_register[reg] = val;
		}
		break;
	case HLT:
		Show(HLT);
		m_isRunning = false;
		break;
	default:
		break;
	}

	++m_register[IP];
}

RegisterCode VirtualMachine::RegisterName(ValueType regCode)
{
	if (regCode > static_cast<ValueType>(NREG) ||
		(regCode < static_cast<ValueType>(OUT)))
	{
		return RegisterCode::NREG;
	}
	return static_cast<RegisterCode>(regCode);
}

void VirtualMachine::Skip(ValueType val)
{
	do
	{
		val--;
		++m_register[IP];
	} while (val > 0);
}
