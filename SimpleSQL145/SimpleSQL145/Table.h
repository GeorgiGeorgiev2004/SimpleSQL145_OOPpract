#pragma once
#include "Col.h"
#include "MyString.h"
class Table 
{
	MyString name = nullptr;
	Col* cols = nullptr;

	int size = 0;
	int capacity = 0;

	void copyFrom(const Table& other);
	void free();
	void moveFrom(Table&& other);
	void resize();

public:
	Table();
	Table(const Table&);
	Table& operator=(const Table&);
	Table(Table&& other) noexcept;
	Table& operator=(Table&& other) noexcept;
	~Table();

	MyString getName() const;
	void setName(MyString _name);

	Table CreateTable();
	
	bool AddCol(Col& col);
};
	