#pragma once
#include "Table.h"
#include "MyString.h"
#include "SQLResponse.h"
#include "ValueFactory.h"


class Database 
{
	MyString path;
	Table* tables;

	int count;
	int cap;

	void copyFrom(const Database& other);
	void free();
	void moveFrom(Database&& other);
	void resize();

public:
	Database();
	Database(MyString path);
	Database(const Database& other);
	Database& operator=(const Database& other);
	Database(Database&& other) noexcept;
	Database& operator=(Database&& other) noexcept;
	~Database();

	Table CreateTable(const MyString);
	bool DeleteTable(const MyString& name);

	SQLResponse executeQuerry(const MyString&);

	bool ReadTablesFromFile(const MyString& path);
	bool AddTableToDb(const Table& tb);

	bool SaveInFile(const MyString& path);

	bool ContainsTable(const Table& tab,int& i);
	bool ContainsTable(const Table& tab);

	bool ShowTables();
	SQLResponse PrintTableById(const int id);
};