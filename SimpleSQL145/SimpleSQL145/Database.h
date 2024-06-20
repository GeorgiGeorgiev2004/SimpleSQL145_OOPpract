#pragma once
#include "Table.h"
#include "MyString.h"
class Database 
{
	MyString name=nullptr;
	Table* tables = nullptr;

	Database();
	Database(char* _name);
	Database(const Database& other);
	Database& operator=(const Database& other);
	Database(Database&& other) noexcept;
	Database& operator=(Database&& other) noexcept;
	~Database();


	void CreateTable();
	void DeleteTable();
};