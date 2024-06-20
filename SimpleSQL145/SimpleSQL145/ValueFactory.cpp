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