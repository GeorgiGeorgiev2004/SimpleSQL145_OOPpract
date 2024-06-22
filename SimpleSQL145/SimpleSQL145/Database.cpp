#pragma once 
#include "Database.h"
#include <iostream>
#include <fstream>

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
	tables = new Table[cap];
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

bool Database::DeleteTable(MyString& name)
{
	for (size_t i = 0; i < count; i++)
	{
		if (tables[i].getName()==name)
		{
			std::swap(tables[i], tables[count-1]);
			tables[count - 1].~Table();
			return true;
		}
	}

	return false;
};

bool Database::ReadTablesFromFile(MyString& path)
{
	std::ifstream ifs(path.c_str());
	if (!ifs.is_open())
	{
		std::cout << "File couldn't open properly";
		return false;
	}
	while (!ifs.eof())
	{
		int _count, _cap;
		ifs >> _count;
		ifs >> _cap;
		if (_cap>count)
		{
			count = _count;
			cap = _cap;
		}
		else
		{
			std::cout<< "Corrupted file! More elements than array space!\n";
			return false;
		}
		for (size_t i = 0; i < count; i++)
		{
			ifs >> tables[i];
		}
	}
	return false;
}

bool Database::AddTableToDb(Table& tb)
{
	return false;
}

bool Database::SaveInFile(MyString& path)
{
	std::ofstream ofs(path.c_str(), std::ios::app);
	ofs<< count << " " << cap<<" ";
	for (size_t i = 0; i < count; i++)
	{
		ofs << tables[i];
	}
	return true;
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
