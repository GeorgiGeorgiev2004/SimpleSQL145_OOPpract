#include "Col.h"
#include <Text.h>
#include <Integer.h>
#include <Real.h>

void Col::free()
{
	name = " ";
	for (size_t i = 0; i < size; i++)
		delete val[i];
	delete[] val;
}

void Col::copyFrom(const Col& other)
{
	name = other.name;
	val = new Value * [other.capacity];
	size = other.size;
	capacity = other.capacity;
	type = other.type;

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
	name = other.name;
	type = other.type;

	val = other.val;
	other.val = nullptr;

	other.type = ValueType::integer;
	other.size = other.capacity = 0;
	other.name = "";
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
	type = ValueType::integer;
	name = "";
	capacity = 8;
	size = 0;
	val = new  Value * [capacity];
};
Col::Col(const Col& other)
{
	copyFrom(other);
}
Col::Col(MyString _name, ValueType _type)
{
	name = _name;
	type = _type;
	capacity = 8;
	size = 0;
	val = new  Value * [capacity];
}
;
Col& Col::operator=(const Col& other)
{
	if (this != &other)
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
}


ValueType Col::getType() const
{
	return type;
}
int Col::getSize() const
{
	return this->size;
}
MyString Col::getName() const
{
	return MyString(this->name);
}
;
void Col::setType(ValueType valt)
{
	type = valt;
}
void Col::printValueAtIndex(uint16_t index)
{
	if (index>=size)
	{
		std::cout << "Error: Index out of bounds.";
		return;
	}
	else
	{
	  this->val[index]->printValue();
	}
}
;

std::ostream& operator<<(std::ostream& os, const Col& obj)
{
	os << obj.name << " " << obj.size << " " << obj.capacity << " " << (int)obj.type << " ";

	for (size_t i = 0; i < obj.size; i++)
	{
		//Controversial desicion. Could be done with unique pointers.
		//Mid session I lack the time to spend on figuring that out as well.
		switch ((ValueType)obj.type)
		{
		case ValueType::text:
		{
			Text* t = dynamic_cast<Text*> (obj.val[i]);
			Text tt = *t;             // <--- This should not be mandatory. control+lmb led me to false references otherwise. This fixes it.
			return os << tt << " ";
		}
		case ValueType::integer: {
			Integer* t = dynamic_cast<Integer*> (obj.val[i]);
			Integer tt = *t;
			return os << tt << " ";
		}
		case ValueType::real: {
			Real* t = dynamic_cast<Real*> (obj.val[i]);
			Real tt = *t;
			return os << tt << " ";
		}
		default:
			break;
		}
	}
	return os;
}

std::istream& operator>>(std::istream& is, Col& obj)
{
	int type = 0;
	is >> obj.name >> obj.size >> obj.capacity >> type;
	obj.type = (ValueType)type;
	for (size_t i = 0; i < obj.size; i++)
	{
		switch ((ValueType)obj.type)
		{
		case ValueType::text: {
			Text* t = dynamic_cast<Text*> (obj.val[i]);
			Text tt = *t;
			return is >> tt;
		}
		case ValueType::integer: {
			Integer* t = dynamic_cast<Integer*> (obj.val[i]);
			Integer tt = *t;
			return is >> tt;
		}
		case ValueType::real: {
			Real* t = dynamic_cast<Real*> (obj.val[i]);
			Real tt = *t;
			return is >> tt;
		}
		default:
			break;
		}
	}
	return is;
}
