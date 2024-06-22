#pragma once

enum class Responses
{
	Querry_OK,
	Rows_affected,
	Querry_Bad
};

class SQLResponse
{
public:
	Responses code;
	size_t rowsAffected;

};