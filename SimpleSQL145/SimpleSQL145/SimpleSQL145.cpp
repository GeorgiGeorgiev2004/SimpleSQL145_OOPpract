#include <iostream>
#include "SQLResponse.h"
#include "Database.h"
int main()
{
    MyString path = "test.txt";
  /*Database db(path);
    db.ShowTables();

    Table t = Table("Stefan");
    t.CreateTable();

    MyString name1 = "name1";
    ValueType vt1 = ValueType::integer;
    MyString name2 = "name2";
    ValueType vt2 = ValueType::text;

    Col c1 = Col(name1,vt1);
    t.AddCol(c1);
    Col c2 =Col(name2, vt2);
    t.AddCol(c2);
    
    db.AddTableToDb(t);
    db.SaveInFile(path);
    
    db.ReadTablesFromFile(path);

    db.ShowTables();*/

    MyString a= "create table test_table (field1 int, field2 real, field12 int, field11 int);";
    Database db(path);
    SQLResponse aaa = db.executeQuerry(a);
}