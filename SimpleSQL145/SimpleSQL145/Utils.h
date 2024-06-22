#pragma once
#include "Database.h"

MyString* SplitString(const char* str, const char del, int& size, int& countOfCommas, int& countOfParentasL);

void DeleteArgs(MyString* args, int size);

int GetType(MyString);