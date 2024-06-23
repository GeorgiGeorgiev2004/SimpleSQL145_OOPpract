#pragma once
#include "Value.hpp"

class Real : public Value
{
	double value=0.0;
public:
	Real();
	Real(double val);
	Value* clone() const override;
	void printValue() const override;

	friend std::ostream& operator<<(std::ostream& os, const Real& obj);
	friend std::istream& operator>>(std::istream& is, Real& ref);

	void setValue(double val);
	double getValue() const;
};
