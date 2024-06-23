#pragma once 
#include "Database.h"
#include "Utils.h"
#include"Integer.h"
#include"Real.h"

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
	Table* newCollection = new Table[cap *= 2];
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

bool Database::DeleteTable(const MyString& name)
{
	for (size_t i = 0; i < count; i++)
	{
		if (tables[i].getName() == name)
		{
			std::swap(tables[i], tables[count - 1]);
			tables[count - 1] = Table();
			count--;
			return true;
		}
	}

	return false;
};

bool Database::ReadTablesFromFile(const MyString& path)
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

bool Database::AddTableToDb(const Table& tb)
{
	if (cap == count)
	{
		resize();
	}
	tables[count++] = tb;
	return true;
}

bool Database::SaveInFile(const MyString& path)
{
	std::ofstream ofs(path.c_str(), std::ios::app);
	ofs << count << " " << cap << " ";
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
		if (count == 0)
		{
			std::cout << "Empty set \n";
			return true;
		}
		else
		{
			std::cout << plusANDdash + plusANDdash + finisher + "\n";
			std::cout << "|Tables_in_" << this->path << " |\n";
		}
		for (size_t i = 0; i < count; i++)
		{
			std::cout << plusANDdash + plusANDdash + finisher + "\n";
			std::cout << tables[i].getName() << "\n";
		}
		std::cout << plusANDdash + plusANDdash + finisher + "\n";
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
	if (id > count)
	{
		std::cout << "Error: Out of bounds";
	}
	this->tables[id].PrintTable();
	return ans;
};
bool Database::ContainsTable(const Table& tab, int& index)
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
	return ContainsTable(tab, i);
}


SQLResponse Database::executeQuerry(const MyString& str)
{
	SQLResponse ans;
	ans.rowsAffected = 0;
	int CountOfArguments = 0;
	int CountComma = 0;
	int CountPare = 0;
	MyString* args = SplitString(str.c_str(), ' ', CountOfArguments, CountComma, CountPare);
	if (args == nullptr)
	{
		ans.code = Responses::Querry_Bad;
		DeleteArgs(args, CountOfArguments);
		return ans;
	}
	if (args[0] == "show" && args[1] == "tables")
	{
		if (this->ShowTables())
		{
			ans.code = Responses::Querry_OK;
			ans.rowsAffected = 0;
			DeleteArgs(args, CountOfArguments);
			return ans;
		}
	}
	else if (args[0] == "drop" && args[1] == "table")
	{
		if (this->DeleteTable(args[2]))
		{
			ans.code = Responses::Querry_OK;
			ans.rowsAffected = 0;
			DeleteArgs(args, CountOfArguments);
			return ans;
		}
	}
	else if (args[0] == "create" && args[1] == "table")
	{
		Table t = this->CreateTable(args[2]);
		for (size_t i = 3; i <= CountComma * 2 + 3; i += 2)//3 to nullify the starting possition *2 for the pairs of name-value
		{
			int type = GetType(args[i + 1]);
			if (type == -1)
			{
				ans.code = Responses::Querry_Bad;
				DeleteArgs(args, CountOfArguments);
				return ans;
			}
			Col col = Col(args[i].c_str(), (ValueType)type);
			t.AddCol(col);
		}
		AddTableToDb(t);
		ans.code = Responses::Querry_OK;
		ans.rowsAffected = 1;
	}
	else if (args[0] == "insert" && args[1] == "into")
	{
		int i = 0;
		if (!ContainsTable(Table(args[2]), i))
		{
			ans.code = Responses::Querry_Bad;
			DeleteArgs(args, CountOfArguments);
			return ans;
		}
		Table t = Table(tables[i]);
		int j = 3;
		int workingFields = 0;
		while (args[j] != MyString("values")) //In general I have not implemented validation for key words and names so this will most definetly break. I will either forget or run out of time.
		{
			if (!t.ContainsCol(args[j]))
			{
				std::cout << "There is no column with the name " << args[j].c_str();
				ans.code == Responses::Querry_Bad;
				ans.rowsAffected = 0;
				DeleteArgs(args, CountOfArguments);
				return ans;
			}
			j++;
		}
		workingFields = j - 3;
		j++;
		for (size_t i = 0; i < workingFields; i++)
		{
			ValueType vt = t.GetTypeOfColByInd(i);
			for (size_t k = j; k <= CountPare * workingFields + 3; k += workingFields)
			{
				Value* val = valueFactory(vt, args[k]);
				t.AddValueInCol(i, *val);
			}
			ans.rowsAffected++;
		}
		this->tables[i] = t;
	}
	else if (args[0] == "select")
	{
		int j = 1;
		while (args[j] != MyString("from"))
		{
			j++;
		}
		j--;
		int tableIND = 0;
		if (!this->ContainsTable(args[j]), tableIND)
		{
			ans.code = Responses::Querry_Bad;
			DeleteArgs(args, CountOfArguments);
			return ans;
		}
		if (j == 1 && args[j] == MyString("*"))
		{
			this->PrintTableById(tableIND);
			ans.code = Responses::Querry_OK;
			return ans;
		}
		else
		{
			for (size_t i = 1; i < 1 + j; i++)
			{
				MyString st(args[i]);
				if (!this->tables[tableIND].ContainsCol(st))
				{
					ans.code = Responses::Querry_Bad;
					DeleteArgs(args, CountOfArguments);
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
	else if (args[0] == "alter" && args[1] == "table")
	{
		int index = 0;
		if (!this->ContainsTable(args[2]), index)
		{
			ans.code = Responses::Querry_Bad;
			DeleteArgs(args, CountOfArguments);
			return ans;
		}
		if (args[3] == "add")
		{
			if (this->tables[index].ContainsCol(args[4]))
			{
				ans.code = Responses::Querry_Bad;
				ans.rowsAffected = 0;
				DeleteArgs(args, CountOfArguments);
				return ans;
			}
			int type = GetType(args[5]);
			if (type == -1)
			{
				ans.code = Responses::Querry_Bad;
				ans.rowsAffected = 0;
				DeleteArgs(args, CountOfArguments);
				return ans;
			}
			Col col = Col(args[4].c_str(), (ValueType)type);
			this->tables[index].AddCol(col);
			ans.rowsAffected= tables[index].GetRows();
			ans.code = Responses::Querry_OK;
		}
		else if (args[3] == "rename")
		{
			int colind = 0;
			if (!this->tables[index].ContainsCol(args[5],colind))
			{
				ans.code = Responses::Querry_Bad;
				DeleteArgs(args, CountOfArguments);
				ans.rowsAffected = 0;
				return ans;
			}
			else
			{
				this->tables[index].RenameCol(args[7], colind);
				ans.code = Responses::Querry_OK;
				ans.rowsAffected = 1;
			}
		}
		else if (args[3] == "drop")
		{
			Col a(args[5], ValueType::integer);
			int n=tables[index].GetRows();
			if (this->tables[index].RemoveCol(a))
			{
				ans.code = Responses::Querry_OK;
				ans.rowsAffected = n;
				ans.rowsAffected = tables[0].GetRows();
			}
		}
	}
	else if (args[0] == "update")
	{
		int index = 0;
		if (!this->ContainsTable(args[1]), index)
		{
			ans.code = Responses::Querry_Bad;
			DeleteArgs(args, CountOfArguments);
			return ans;
		}
		int colIndex = 0;
		if (!this->tables[index].ContainsCol(args[3], colIndex))
		{
			ans.code = Responses::Querry_Bad;
			DeleteArgs(args, CountOfArguments);
			std::cout << "No column of the name: " << args[3] << " found!\n";
			return ans;

		}
		switch (CountOfArguments)
		{
		case 6:
		{
			Col a(args[3], this->tables[index].GetTypeOfColByInd(colIndex));
			for (size_t i = 0; i < this->tables[index].GetRows(); i++)
			{
				Value* val = valueFactory(a.getType(), args[5]);
				a.AddValue(*val);
			}
			this->tables[index].RemoveCol(a);
			this->tables[index].AddCol(a);
		}
		break;
		case 10:
		{
			int indexChange = colIndex;
			int ConditionIndex = 0;
			if (!this->tables[index].ContainsCol(args[7], ConditionIndex))
			{
				ans.code = Responses::Querry_Bad;
				DeleteArgs(args, CountOfArguments);
				std::cout << "No column of the name: " << args[7] << " found!\n";
				return ans;

			}

			Col* change = this->tables[index].GetColById(indexChange);
			Col* condition = this->tables[index].GetColById(ConditionIndex);
			switch (condition->getType())
			{
			case ValueType::integer:
				for (size_t i = 0; i < this->tables->GetRows(); i++)
				{
					Value* v = condition->GetValueAtIndex(i);
					Integer* t = dynamic_cast<Integer*> (v);
					int value = t->getValue();
					switch (args[8][0])
					{
					case '<':
						if (t->getValue()< atoi(args[9].c_str()))
						{
							Integer in = Integer(atoi(args[5].c_str()));
							change->AddValueAt(in, i);
						}
						break;
					case'=':
						if (t->getValue() == atoi(args[9].c_str()))
						{
							Integer in = Integer(atoi(args[5].c_str()));
							change->AddValueAt(in, i);
						}
						break;
					case'>':
						if (value > atoi(args[9].c_str()))
						{
							Integer in = Integer(atoi(args[5].c_str()));
							change->AddValueAt(in, i);
						}
						break;
					default:
						break;
					}
				}
				break;
			case ValueType::real:
				for (size_t i = 0; i < this->tables->GetRows(); i++)
				{
					Real* t = dynamic_cast<Real*> (condition->GetValueAtIndex(i));
					double value = t->getValue();
					switch (args[8][0])
					{
					case '<':
						if (value - atoi(args[9].c_str())<0.001)
						{
							Real in = Real(atoi(args[5].c_str()));
							change->AddValueAt(in, i);
						}
						break;
					case'=':
						if (value - atoi(args[9].c_str())==0.001)
						{
							Real in = Real(atoi(args[5].c_str()));
							change->AddValueAt(in, i);
						}
						break;
					case'>':
						if (value - atoi(args[9].c_str())>0.001)
						{
							Real in = Real(atoi(args[5].c_str()));
							change->AddValueAt(in, i);
						}
						break;
					default:
						break;
					}
				}
			}
		}
		break;
		case 14:
		{

		}
		break;
		default:
			break;
		}
	}
	else
	{
		ans.code = Responses::Querry_Bad;
		ans.rowsAffected = 0;
		std::cout << "Unknown command!\n";
	}
	DeleteArgs(args, CountOfArguments);
	return ans;
}

Table Database::CreateTable(MyString _name)
{
	return Table(_name);
}