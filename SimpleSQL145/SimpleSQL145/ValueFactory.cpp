#pragma once
#include "ValueFactory.h"
#include "Integer.h"
#include "Text.h"
#include "Real.h"


Value* valueFactory(ValueType type)
{
	switch (type)
	{
	case ValueType::text:
		return new Text();
	case ValueType::integer:
		return new Integer();
	case ValueType::real:
		return new Real();
	}
	return nullptr;
}
Value* valueFactory(ValueType type,Value& val)
{
	switch (type)
	{
	case ValueType::text:
	{
		Text* t = dynamic_cast<Text*> (&val);
		return t;
	}
	case ValueType::integer: {
		Integer* t = dynamic_cast<Integer*> (&val);
		return t;
	}
	case ValueType::real: {
		Real* t = dynamic_cast<Real*> (&val);
		return t;
	}
	default:
		break;
	}
}

Value* valueFactory(ValueType type, MyString& mstr)
{
	switch (type)
	{
	case ValueType::text:
	{
		return new Text(mstr);
	}
	case ValueType::integer: {
		return new Integer(atoi(mstr.c_str()));
	}
	case ValueType::real: {
		return new Real(atof(mstr.c_str()));
	}
	default:
		break;
	}
	return nullptr;
}
