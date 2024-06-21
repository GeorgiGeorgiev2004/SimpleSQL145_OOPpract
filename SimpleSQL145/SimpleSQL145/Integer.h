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

	void setValue(int val);
	int getValue() const;
};