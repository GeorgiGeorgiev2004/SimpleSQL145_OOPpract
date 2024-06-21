#pragma once
#include "Table.h"
#include "MyString.h"
class Database 
{
	MyString path = nullptr;
	Table* tables = nullptr;

	int count = 0;
	int cap = 0;

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


	bool ShowTables();
};