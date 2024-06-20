#pragma once
#include "Value.hpp"

class Real : public Value
{
	double value;
public:
	Real();
	Real(double val);
	Value* clone() const override;
	void printValue() const override;
};
