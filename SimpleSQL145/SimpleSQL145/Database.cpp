#pragma once 
#include "Database.h"

void Database::copyFrom(const Database& other)
{
	count = other.count;
	path = other.path;
	cap = other.cap;
	tables = new Table[cap];
	for (size_t i = 0; i < count; i++)
	{
		tables[i] = other.tables[i];
	}
}

void Database::free()
{
	path = "";
	cap = 8;
	count = 0;
	delete[] tables;
}

void Database::moveFrom(Database&& other)
{
	count = other.count;
	cap = other.cap;
	path = other.path;

	tables = other.tables;
	other.tables = nullptr;

	other.path = "";
	other.count = 0;
}

void Database::resize()
{
	Table* newCollection = new Table [cap *= 2];
	for (size_t i = 0; i < count; i++)
		newCollection[i] = tables[i];
	delete[] tables;
	tables = newCollection;
}

Database::Database()
{
	path = "";
	cap = 8;
	count = 0;
}

Database::Database(MyString path)
{
	this->path = path;
}

Database::Database(const Database& other)
{
	copyFrom(other);
}

Database& Database::operator=(const Database& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Database::Database(Database&& other) noexcept
{
	moveFrom(std::move(other));
}

Database& Database::operator=(Database&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Database::~Database()
{
	free();
}

bool Database::CreateTable(MyString& tableName)
{

}

bool Database::DeleteTable()
{

}

bool Database::ShowTables()
{
	try
	{
		if (count==0)
		{
			std::cout << "Empty set";
			return true;
		}
		for (size_t i = 0; i < count; i++)
		{
			std::cout << tables[i].getName()<<"\n";
		}
	}
	catch (const std::exception&)
	{
		return false;
	}
	return true;
}
