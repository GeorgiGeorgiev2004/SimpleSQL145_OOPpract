#pragma once
#include "Utils.h"
#include "MyString.h"
bool SplitString(const char* str, const char del, char** res,int& size)
{
	MyString word;
	int i = 0;
	while (str[i]!='\0')
	{
		if (str[i]==del)
		{
			if (word.getSize()!=0)
			{
				const char* a= word.c_str();
				//res[size++] = a;
			}
		}
	}
	return true;
}

void DeleteArgs(char** args,int size)
{
	for (size_t i = 0; i < size; i++)
	{
		delete[] args[i];
	}
	delete args;
}
