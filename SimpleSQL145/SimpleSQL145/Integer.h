#pragma once
#include"Value.hpp"
class Integer : public Value
{
	int value = 0;

public:
	Integer();
	Integer(int val);
	Value* clone() const override;
	void printValue() const override;

	friend std::ostream& operator<<(std::ostream& os, const Integer& obj);
	friend std::istream& operator>>(std::istream& is, Integer& ref);

	void setValue(int val);
	int getValue() const;
};