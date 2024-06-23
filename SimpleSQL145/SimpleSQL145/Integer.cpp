#pragma once
#include "Value.hpp"
#include"Integer.h"

void Integer::printValue() const
{

	std::cout << value;
}

void Integer::setValue(int val)
{
	value = val;
}

int Integer::getValue() const
{
	return value;
}

Integer::Integer()
{
	value = 0;
}
Integer::Integer(int val)
{
	HasValue = true;
	value = val;
}
Value* Integer::clone() const 
{
	return new Integer(*this);
}

std::ostream& operator<<(std::ostream& os, const Integer& obj)
{
	return os << obj.value<<" ";
}

std::istream& operator>>(std::istream& is, Integer& obj)
{
	return is >> obj.value;
}
