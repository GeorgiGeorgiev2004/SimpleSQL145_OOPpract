#pragma once
#include "Utils.h"
#include "MyString.h"


MyString* SplitString(const char* str, const char del, int& size,int& countOfCommas,int&countOfParentasL)
{
	int countOfWS = 0;
	int k = 0;
	while (str[k]!='\0')
	{
		if (str[k]==' ')
		{
			countOfWS++;
		}
		k++;
	}
	k = 0;
	countOfWS++;
	size = countOfWS;
	MyString* result = new MyString[countOfWS];
	MyString word="";
	for (size_t i = 0; i < countOfWS-1;)
	{
		int j = 0;
		while (str[j]!='\0')
		{
			if (str[j] == ',' || str[j] == '(' || str[j] == ')')
			{
				if (str[j] == ',')
				{
					countOfCommas++;
				}if (str[j] == '(')
				{
					countOfParentasL++;
				}
				j++;
				continue;
			}
			if (str[j] == ' '||str[j]==';')
			{
				result[k++] = word;
				word = "";
				i++;
				j++;
				continue;
			}
			else
			{
				word += str[j];
			}
			j++;
		}
	}
	return result;
}

void DeleteArgs(MyString* args,int size)
{
	delete[] args;
}

int GetType(const MyString str)
{
	if (strcmp(str.c_str(),"int")==0)
	{
		return (int)ValueType::integer;
	}
	if (strcmp(str.c_str(), "real") == 0)
	{
		return (int)ValueType::real;
	}
	if (strcmp(str.c_str(), "text") == 0)
	{
		return (int)ValueType::text;
	}
	return-1;
}
