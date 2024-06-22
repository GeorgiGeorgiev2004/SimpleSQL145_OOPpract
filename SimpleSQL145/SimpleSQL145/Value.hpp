#pragma once
#include "MyString.h"
enum class ValueType
{
	integer=0, 
	text=1,
	real=2
};

class Value
{
public:
	virtual void printValue() const = 0;

	virtual Value* clone() const = 0;

	virtual ~Value() = default;
};
