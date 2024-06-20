#pragma once
#include <iostream>
#include <iomanip>
#include <string>

//Include had an issue. Properties->C/C++->General->Additional-Directives!!! 
//ISSUE is --> it is a local path so I am not certain if it is simply a Visual Studio problem or a global one.
//			 \  /
//			  \/
#include <MyString.h>

struct Value 
{
	virtual void printValue() const = 0;

	virtual Value* clone() const = 0;

	virtual ~Value() = default;

};
class Integer : public Value
{
	void printValue() const override 
	{
		std::cout << value;
	};
	int value = 0;

public:
	Integer()
	{
		value = 0;
	}
	Integer(int val)
	{
		value = val;
	}
	Value* clone() const override 
	{
		return new Integer(*this);
	};

};
class Text : public Value
{
	void printValue() const override 
	{
		std::cout << value;
	};
	MyString value = "";
	Text(MyString& string) 
	{
		value = string;
	}
};
class Real : public Value
{
	void printValue() const override 
	{
		std::cout << std::setprecision(2) << std::fixed;
		std::cout << value;
	};
	double value;
public:
	Real() 
	{
		value = 0;
	}
	Real(double val) 
	{
		value = val;
	}
	Value* clone() const override
	{
		return new Real(*this);
	};
};

class Col 
{
	MyString name;
	Value** val = nullptr;

	int capacity;
	int size;

	void copyFrom(const Col& other);
	void free();
	void moveFrom(Col&& other);
	void resize();

public:
	Col();
	Col(const Col&);
	Col& operator=(const Col&);
	Col(Col&& other) noexcept;
	Col& operator=(Col&& other) noexcept;
	~Col();
};