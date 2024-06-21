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
