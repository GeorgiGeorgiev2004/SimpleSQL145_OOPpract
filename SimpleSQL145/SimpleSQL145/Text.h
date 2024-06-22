#pragma once
#include "Value.hpp"
class Text : public Value
{
	MyString value;

public:
	Text();
	Text(MyString& string);
	void printValue() const override;
	Value* clone() const override;

	friend std::ostream& operator<<(std::ostream& os, const Text& obj);
	friend std::istream& operator>>(std::istream& is, Text& ref);

	void setValue(MyString val);
	MyString getValue() const;
};