#include "Value.hpp"
#include "Text.h"

void Text::printValue() const
{
	std::cout << value;
};
Text::Text()
{

}
Text::Text(MyString& string)
{
	HasValue = true;
	value = string;
}
Value* Text::clone() const
{
	return new Text(*this);
}

std::ostream& operator<<(std::ostream& os, const Text& obj)
{
	return os << obj.value << " ";
}

std::istream& operator>>(std::istream& is, Text& obj)
{
	return is >> obj.value;
}


MyString Text::getValue() const
{
	return value;
}

void Text::setValue(MyString val)
{
	value = val;
}
