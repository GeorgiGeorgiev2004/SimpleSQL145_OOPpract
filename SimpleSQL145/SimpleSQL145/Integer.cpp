#pragma once
#include "Value.hpp"
#include"Integer.h"

void Integer::printValue() const
{
	std::cout << value;
}

Integer::Integer()
{
	value = 0;
}
Integer::Integer(int val)
{
	value = val;
}
Value* Integer::clone() const 
{
	return new Integer(*this);
}
