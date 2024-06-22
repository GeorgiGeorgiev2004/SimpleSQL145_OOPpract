#pragma once
#include "Table.h"
#include "MyString.h"
#include "SQLResponse.h"

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

	Table CreateTable(MyString);
	bool DeleteTable(MyString& name);

	SQLResponse executeQuerry(MyString);

	bool ReadTablesFromFile(MyString& path);
	bool AddTableToDb(Table& tb);

	bool SaveInFile(MyString& path);

	bool ShowTables();

};