#pragma once
#include "Col.h"
#include "MyString.h"
class Table
{
	MyString name;
	Col* cols = nullptr;

	int size=0;
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
	void setName(const MyString& _name);

	bool PrintTable();
	bool PrintTable(const MyString* mstrp, const int s);

	int GetRows()const;
	Table CreateTable();

	bool ContainsCol(const MyString& mstr);
	
	bool ContainsCol(const MyString& mstr, int& index);

	bool RenameCol(const MyString& mstr,const int index);

	Col* GetColById(const int ind);

	bool AddValueInCol(const int indexCol, const Value& val);
	ValueType GetTypeOfColByInd(const int ind);

	bool AddCol(const Col& col);

	bool RemoveCol(const Col& col);
};
