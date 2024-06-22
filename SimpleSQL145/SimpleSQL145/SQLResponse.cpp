#pragma once
#include "SQLResponse.h"
#include "Utils.h"

//SQLResponse Database::ExecuteQuerry(MyString str)
//{
//	SQLResponse ans;
//	char** args = nullptr;
//	int i = 0;
//	SplitString(str.c_str(), ' ', args, i);
//
//	if (args[0] == "show" && args[1] == "table")
//	{
//		if (this->ShowTables())
//		{
//			ans.code = Responses::Querry_OK;
//			return ans;
//		}
//	}
//	if (args[0] == "create" && args[1] == "table")
//	{
//		Table t = this->CreateTable(args[3]);
//	}
//	DeleteArgs(args, i);
//	return SQLResponse();
//}