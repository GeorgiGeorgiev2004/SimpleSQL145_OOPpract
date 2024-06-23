#include <iostream>
#include "SQLResponse.h"
#include "Database.h"
int main()
{
    MyString path = "test.txt";
    Database db(path);
    //db.ShowTables();

    //Table t = Table("Stefan");
    //t.CreateTable();

    //MyString name1 = "name1";
    //ValueType vt1 = ValueType::integer;
    //MyString name2 = "name2";
    //ValueType vt2 = ValueType::text;

    //Col c1 = Col(name1,vt1);
    //t.AddCol(c1);
    //Col c2 =Col(name2, vt2);
    //t.AddCol(c2);
    //db.AddTableToDb(t);

    //t.PrintTable();
    //
    //db.SaveInFile(path);
    //
    //db.ReadTablesFromFile(path);

    //db.ShowTables();
    //

    MyString b = "create table test_table (field1 int, field2 real);";
    MyString a= "insert into test_table (field1, field2) values (1, 1.0), (2, 2.0);";
    MyString tt= "select * from test_table;";
    MyString ttt = "select field1 from test_table;";
    SQLResponse aa = db.executeQuerry(b);
    SQLResponse aaa = db.executeQuerry(a);
    SQLResponse t1 = db.executeQuerry(tt);
    SQLResponse t2 = db.executeQuerry(ttt);
    db.ShowTables();
    SQLResponse res = db.PrintTableById(0);
}