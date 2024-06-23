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
	Col(MyString _name, ValueType type);
	Col& operator=(const Col&);
	Col(Col&& other) noexcept;
	Col& operator=(Col&& other) noexcept;
	~Col();

	ValueType getType() const;
	int getSize() const;
	MyString getName() const;
	void setName(const MyString& newName);

	Value* GetValueAtIndex(const int ind);

	void setType(const ValueType valt);
	void printValueAtIndex(const uint16_t index);

	bool AddValue(const Value& val);
	bool AddValueAt(const Value& val, const int ind);
	
	friend std::ostream& operator<<(std::ostream& os, const Col& obj);
	friend std::istream& operator>>(std::istream& is, Col& ref);

};