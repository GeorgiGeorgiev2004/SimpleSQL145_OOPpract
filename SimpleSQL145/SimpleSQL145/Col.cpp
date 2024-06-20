#include "Col.h"

void Col::free()
{

	for (size_t i = 0; i < size; i++)
		delete val[i];  
	delete[] val;
}

void Col::copyFrom(const Col& other)
{
	val = new Value * [other.capacity];
	size = other.size;
	capacity = other.capacity;

	for (size_t i = 0; i < size; i++)
	{
		Value* cloned = other.val[i]->clone();
		if (cloned)
			val[i] = cloned;
	}
}

void Col::moveFrom(Col&& other)
{
	size = other.size;
	capacity = other.capacity;

	val = other.val;
	other.val = nullptr;

	other.size = other.capacity = 0;
}

void Col::resize()
{
	Value** newCollection = new Value * [capacity *= 2];
	for (size_t i = 0; i < size; i++)
		newCollection[i] = val[i]; 
	delete[] val;
	val = newCollection;
}
Col::Col() 
{
	name = "";
	capacity = 8;
	size = 0;
};
Col::Col(const Col& other)
{
	copyFrom(other);
};
Col& Col::operator=(const Col& other)
{
	if (this!=&other)
	{
		free();
		copyFrom(other);
	}
	return *this;
};
Col::Col(Col&& other) noexcept 
{
	moveFrom(std::move(other));
};
Col& Col::operator=(Col&& other) noexcept 
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
};
Col::~Col() 
{
	free();
};