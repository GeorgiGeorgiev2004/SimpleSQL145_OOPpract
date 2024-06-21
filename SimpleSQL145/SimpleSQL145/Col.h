#pragma once
#include <iostream>
#include <string>
#include <Value.hpp>
#include "ValueFactory.h"
//Include had an issue. Properties->C/C++->General->Additional-Directives!!! 
//ISSUE is --> it is a local path so I am not certain if it is simply a Visual Studio problem or a global one.
//			 \  /
//			  \/
#include <MyString.h>

class Col 
{
	MyString name;
	ValueType type;
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

	ValueType getType() const;
	void setType(ValueType valt);


	Col CreateCol(MyString _name, ValueType type);
};