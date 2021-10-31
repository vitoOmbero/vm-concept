#pragma once

#include <array>

class Stack
{
public:
	using ValueType = int64_t;
	static const ValueType kMaxSize{ 256 };
	using StackImpl = std::array<ValueType, kMaxSize>;
	static const ValueType kNotAValue{ INT64_MIN };

	Stack(ValueType& stackPointerLValue) :
		m_sp(stackPointerLValue), m_storage()
	{
		m_sp = -1;
		m_storage.fill(-1);
	}

	ValueType Pop()
	{
		return (m_sp >= 0) ? m_storage[m_sp--] : kNotAValue;
	}

	void Push(ValueType val)
	{
		if (m_sp < kMaxSize) {
#pragma warning (disable : 6386)
			m_storage[++m_sp] = val;
		}
	}

	ValueType Peek()
	{
		return (m_sp >= 0) ? m_storage[m_sp] : kNotAValue;
	}

	ValueType* Top()
	{
		return &m_storage[m_sp];
	}

private:
	ValueType& m_sp;
	StackImpl m_storage;
};