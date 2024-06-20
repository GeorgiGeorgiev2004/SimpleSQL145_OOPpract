#include "Value.hpp"
#include "Text.h"

void Text::printValue() const
{
	std::cout << value;
};
Text::Text()
{
	value = "NULL";
}
Text::Text(MyString& string)
{
	value = string;
}
Value* Text::clone() const
{
	return new Text(*this);
}