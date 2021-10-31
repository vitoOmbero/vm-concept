#pragma once

#include <bitset>

class FlagRegister
{
public:
	using ValueType = int64_t;

	// unset ZF means the value != 0
	bool GetZF() { return m_flags[0]; }
	void SetZF(bool v) { m_flags[0] = v; }

	// unset SF means the difference is non-negative
	bool GetSF() { return m_flags[1]; }
	void SetSF(bool v) { m_flags[1] = v; }

private:
	std::bitset<8> m_flags;
};