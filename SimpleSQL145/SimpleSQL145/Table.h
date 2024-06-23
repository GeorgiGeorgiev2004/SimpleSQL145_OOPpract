#pragma once
#include "Col.h"
#include "MyString.h"
class Table
{
	MyString name;
	Col* cols = nullptr;

	int size;
	int capacity = 8;

	void copyFrom(const Table& other);
	void free();
	void moveFrom(Table&& other);
	void resize();

public:
	Table();
	Table(MyString name);
	Table(const Table&);
	Table& operator=(const Table&);
	Table(Table&& other) noexcept;
	Table& operator=(Table&& other) noexcept;
	~Table();

	friend std::ostream& operator<<(std::ostream& os, const Table& obj);
	friend std::istream& operator>>(std::istream& is, Table& ref);

	MyString getName() const;
	void setName(MyString& _name);

	bool PrintTable();

	Table CreateTable();

	bool ContainsCol(MyString& mstr, int& index);

	bool AddCol(Col& col);

	bool RemoveCol(Col& col);
};
