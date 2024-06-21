#include "MyString.h"
#pragma once
enum class ValueType
{
	integer, 
	text,
	real
};

class Value
{
public:
	virtual void printValue() const = 0;

	virtual Value* clone() const = 0;

	virtual ~Value() = default;
};
