#pragma once
#include "Value.hpp"

Value* valueFactory(ValueType type);

Value* valueFactory(ValueType type, Value&);

Value* valueFactory(ValueType type, MyString&);