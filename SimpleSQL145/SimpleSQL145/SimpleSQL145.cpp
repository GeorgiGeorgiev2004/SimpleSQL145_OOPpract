#include <iostream>
#include "SQLResponse.h"
#include "Database.h"
int main()
{
	//As the example failed to clear up suspicions around the white spaces around some parts of the code
	//Please place ws's inbetween all elements of the input and do not forget the ';' at the end.
	//Example : "update table_name set column_name = value where column_name < 3;"

	MyString path = "test.txt";
	Database db(path);
	char* cmd = new char[1024];
	do {
		std::cout << "ssql145>";
		std::cin.getline(cmd, 1023);
		MyString command(cmd);
		if (command == "end")
		{
			break;
		}
		SQLResponse res = db.executeQuerry(command);
		switch (res.code)
		{
		case Responses::Querry_OK:
			std::cout << "Querry_OK\n";
			std::cout << "rows affected: " << res.rowsAffected << "\n";
			break;
		case Responses::Querry_Bad:
			std::cout << "Querry_Bad\n";
			std::cout << "rows affected: " << res.rowsAffected << "\n";
			break;
		default:
			break;
		}
	} while (true);

	delete[] cmd;

	//MyString c1 = "show tables;";
	//MyString c2 = "create table test_table (field1 int, field2 real);";
	//MyString c3 = "select * from test_table;";
	//MyString c4 = "insert into test_table (field1, field2) values (1, 1.0), (2, 2.0);";
	//MyString c5 = "select * from test_table;";
	//MyString c6 = "insert into test_table (field1) values (3), (4);";
	//MyString c7 = "select * from test_table;";
	//MyString c8 = "alter table test_table add field3 int;";
	//MyString c9 = "select * from test_table;";
	//MyString c10 = "alter table test_table drop column field2;";
	//MyString c11 = "select * from test_table;";
	//MyString c12 = "alter table test_table rename column field3 to field2;";
	//MyString c13 = "select * from test_table;";
	//MyString c14 = "update test_table set field2=0.0;";

	//
	//
	//SQLResponse res1 = db.executeQuerry(c1);
	//SQLResponse res2 = db.executeQuerry(c2);
	//SQLResponse res3 = db.executeQuerry(c3);
	//SQLResponse res4 = db.executeQuerry(c4);
	//SQLResponse res5 = db.executeQuerry(c5);
	//SQLResponse res6 = db.executeQuerry(c6);
	//SQLResponse res7 = db.executeQuerry(c7);
	//SQLResponse res8 = db.executeQuerry(c8);
	//SQLResponse res9 = db.executeQuerry(c9);
	//SQLResponse res10 = db.executeQuerry(c10);
	//SQLResponse res11 = db.executeQuerry(c11);
	//SQLResponse res12 = db.executeQuerry(c12);
	//SQLResponse res13 = db.executeQuerry(c13);
	//SQLResponse res14 = db.executeQuerry(c14);
	//SQLResponse res15 = db.executeQuerry(c1);
}