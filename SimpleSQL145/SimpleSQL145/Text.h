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

	void setValue(MyString val);
	MyString getValue() const;
};