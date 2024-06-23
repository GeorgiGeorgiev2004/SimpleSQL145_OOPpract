#pragma once 
#include "Database.h"
#include "Utils.h"

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
	cap = 8;
	count = 0;
	tables = new Table[cap];
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
			tables[count - 1]=Table();
			count--;
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
		std::cout << "File couldn't open properly \n";
		return false;
	}
	int _count, _cap;
	ifs >> _count;
	ifs >> _cap;
	if (_cap > count)
	{
		count = _count;
		cap = _cap;
	}
	else
	{
		std::cout << "Corrupted file! More elements than array space!\n";
		return false;
	}
	for (size_t i = 0; i < count; i++)
	{
		ifs >> tables[i];
	}
	
	return false;
}

bool Database::AddTableToDb(Table& tb)
{
	if (cap==count)
	{
		resize();
	}
	tables[count++] = tb;
	return true;
}

bool Database::SaveInFile(MyString& path)
{
	std::ofstream ofs(path.c_str(), std::ios::app);
	ofs<< count << " " << cap<<" ";
	for (size_t i = 0; i < count; i++)
	{
		ofs << tables[i];
	}
	ofs.close();
	return true;
}
bool Database::ShowTables()
{
	try
	{
		if (count==0)
		{
			std::cout << "Empty set \n";
			return true;
		}
		for (size_t i = 0; i < count; i++)
		{
			std::cout <<plusANDdash+plusANDdash+finisher+"\n";
			std::cout << tables[i].getName()<<"\n";
		}
		std::cout << plusANDdash + plusANDdash + finisher+"\n";
	}
	catch (const std::exception&)
	{
		return false;
	}
	return true;
}
SQLResponse Database::PrintTableById(int id)
{
	SQLResponse ans;
	ans.code = Responses::Querry_OK;
	if (id>count)
	{
		std::cout << "Error: Out of bounds";
	}
	this->tables[id].PrintTable();
	return ans;
};
bool Database::ContainsTable(const Table& tab,int& index)
{
	for (size_t i = 0; i < count; i++)
	{
		if (tables[i].getName() == tab.getName())
		{
			index = i;
			return true;
		}
	}
	return false;
}
bool Database::ContainsTable(const Table& tab)
{
	int i = 0;
	return ContainsTable(tab,i);
}


SQLResponse Database::executeQuerry(MyString str)
{
	SQLResponse ans;
	int i = 0;
	int CountComma = 0;
	int CountPare = 0;
	MyString* args = SplitString(str.c_str(), ' ', i,CountComma,CountPare);
	if (args==nullptr)
	{
		ans.code = Responses::Querry_Bad;
		DeleteArgs(args, i);
		return ans;
	}
	if (args[0] == "show" && args[1] == "table")
	{
		if (this->ShowTables())
		{
			ans.code = Responses::Querry_OK;
			DeleteArgs(args, i);
			return ans;
		}
	}
	if (args[0] == "drop" && args[1] == "table")
	{
		if (this->DeleteTable(args[2]))
		{
			ans.code = Responses::Querry_OK;
			DeleteArgs(args, i);
			return ans;
		}
	}
	if (args[0] == "create" && args[1] == "table")
	{
		Table t = this->CreateTable(args[2]);
		for (size_t i = 3; i <= CountComma*2+3; i+=2)//3 to nullify the starting possition *2 for the pairs of name-value
		{
			int type = GetType(args[i + 1]);
			if (type==-1)
			{
				ans.code = Responses::Querry_Bad;
				DeleteArgs(args, i);
				return ans;
			}
			Col col = Col(args[i].c_str(), (ValueType)type);
			t.AddCol(col);
		}
		AddTableToDb(t);
		ans.code = Responses::Querry_OK;
		ans.rowsAffected = 1;
	}
	if (args[0] == "insert" && args[1] == "into")
	{
		int i = 0;
		if (!ContainsTable(Table(args[2]),i))
		{
			ans.code = Responses::Querry_Bad;
			DeleteArgs(args, i);
			return ans;
		}
		Table t = Table(tables[i]);
		int j = 3;
		int workingFields = 0;
		while (args[j]!=MyString("values")) //In general I have not implemented validation for key words and names so this will most definetly break. I will either forget or run out of time.
		{
			if (!t.ContainsCol(args[j]))
			{
				std::cout << "There is no column with the name " << args[j].c_str();
				ans.code == Responses::Querry_Bad;
				DeleteArgs(args, i);
				return ans;
			}
			j++;
		}
		workingFields = j - 3;
		j++;
		for (size_t i = 0; i < workingFields; i++)
		{
			ValueType vt = t.GetTypeOfColByInd(i);
			for (size_t k = j; k <= CountPare * 2+3; k+=workingFields)
			{
				Value* val = valueFactory(vt, args[k]);
				t.AddValueInCol(i, *val);
			}
		}
		this->tables[i] = t;
	}
	if (args[0] == "select")
	{
		int j = 1;
		while (args[j] != MyString("from")) 
		{
			j++;
		}
		j--;
		int tableIND = 0;
		if (!this->ContainsTable(args[j]),tableIND)
		{
			ans.code = Responses::Querry_Bad;
			DeleteArgs(args, i);
			return ans;
		}
		if (j==1&&args[j]==MyString("*"))
		{
			this->PrintTableById(tableIND);
			ans.code = Responses::Querry_OK;
			return ans;
		}
		else
		{
			for (size_t i = 1; i < 1+j; i++)
			{
				MyString st(args[i]);
				if (!this->tables[tableIND].ContainsCol(st))
				{
					ans.code = Responses::Querry_Bad;
					DeleteArgs(args, i);
					return ans;
				}
			}
			MyString* st = new MyString[j];
			for (size_t i = 1; i < 1 + j; i++)
			{
				st[i - 1] = MyString(args[i]);
			}
			this->tables[tableIND].PrintTable(st, j);
			delete[] st;
		}
	}
	DeleteArgs(args, i);
	return ans;
}

Table Database::CreateTable(MyString _name)
{
	return Table(_name);
}