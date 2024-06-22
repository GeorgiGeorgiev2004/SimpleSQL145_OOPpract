#include "Value.hpp"
#include "Real.h"

#include <iomanip>

void Real::printValue() const
{
	std::cout << std::setprecision(2) << std::fixed;
	std::cout << value;
}
void Real::setValue(double val)
{
	value = val;
}
double Real::getValue() const
{
	return value;
}
;
Real::Real()
{
	value = 0;
}
Real::Real(double val)
{
	value = val;
}
Value* Real::clone() const
{
	return new Real(*this);
};

std::ostream& operator<<(std::ostream& os, const Real& obj)
{
	return os << obj.value << " ";
}

std::istream& operator>>(std::istream& is, Real& obj)
{
	return is >> obj.value;
}
