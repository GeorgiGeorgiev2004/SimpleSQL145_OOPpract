#pragma once
#include "Database.h"

MyString* SplitString(const char* str, const char del, int& size, int& countOfCommas, int& countOfParentasL);

void DeleteArgs(MyString* args, int size);
static const MyString plusANDdash = "+-------";
static const MyString finisher = "+";

int GetType(MyString);

void PrintALine(int size);