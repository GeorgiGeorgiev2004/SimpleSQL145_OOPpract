#pragma once
#include "Table.h"
#include "Utils.h"
#include <SQLResponse.h>

void Table::free()
{
	name = " ";
	delete[] cols;
}

void Table::copyFrom(const Table& other)
{
	name = other.name;
	cols = new Col [other.capacity];
	size = other.size;
	capacity = other.capacity;

	for (size_t i = 0; i < size; i++)
	{
		cols[i] = other.cols[i];
	}
}

void Table::moveFrom(Table&& other)
{
	size = other.size;
	capacity = other.capacity;
	name = other.name;

	cols = other.cols;
	other.cols = nullptr;

	other.name = " ";
	other.size = other.capacity = 0;
}

void Table::resize()
{
	Col* newCollection = new Col [capacity *= 2];
	for (size_t i = 0; i < size; i++)
		newCollection[i] = cols[i];
	delete[] cols;
	cols = newCollection;
}

Table::Table() 
{
	name = "";
	size = 0;
	capacity = 8;
	cols = new Col[capacity];
}
Table::Table(const Table& other)
{
	copyFrom(other);
}
Table::Table(MyString _name)
{
	name = _name;
	size = 0;
	capacity = 8;
	cols = new Col[capacity];
}


Table& Table::operator=(const Table& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
};
Table::Table(Table&& other) noexcept 
{
	moveFrom(std::move(other));
};
Table& Table::operator=(Table&& other) noexcept 
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
};
Table::~Table() 
{
	free();
}
MyString Table::getName() const
{
	return this->name;
}

void Table::setName(MyString& _name)
{
	if (_name==nullptr)
	{
		std::cout << "Name not set!";
		return;
	}
	name = _name;
}

Table Table::CreateTable()
{
	return Table();
}

bool Table::ContainsCol(MyString& mstr, int& index)
{
	for (size_t i = 0; i < size; i++)
	{
		if (mstr==cols[i].getName())
		{
			index = i; 
			return true;
		}
	}
	return false;
}

bool Table::AddCol(Col& col)
{
	if (capacity==size)
	{
		resize();
	}
	cols[size++] = col;
	return true;
}

bool Table::RemoveCol(Col& col)
{
	for (size_t i = 0; i < this->size; i++)
	{
		if (col.getName() == cols[i].getName())
		{
			std::swap(cols[i], cols[size - 1]);
			cols[size - 1] = Col();
			size--;
			return true;
		}
	}
	return false;
}

bool Table::PrintTable()
{
	PrintALine(this->size);
	for (size_t i = 0; i < size; i++)
	{
		std::cout << "| " << this->cols[i].getName();
	}std::cout << " |\n";
	PrintALine(this->size);

	int rows = cols[0].getSize();
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < rows; j++)
		{
			std::cout << "|    ";
			cols[j].printValueAtIndex(i);
			std::cout << " |";
		}
		std::cout << "\n";
	}
	PrintALine(this->size);
	return true;
}

std::ostream& operator<<(std::ostream& os, const Table& obj)
{
	os <<obj.name<< " " << obj.size << " " << obj.capacity << " ";
	for (size_t i = 0; i < obj.size; i++)
	{
		os << obj.cols[i]<<" ";
	}
		return os;
}

std::istream& operator>>(std::istream& is, Table& obj)
{
	is >> obj.name >>obj.size >> obj.capacity;
	for (size_t i = 0; i < obj.size; i++)
	{
		is >> obj.cols[i];
	}
	return is;
}
