#include <iostream>
#include <ostream>
#include "table.h"
#include "Instruction.h"



int main() {
/*
    dataInput testData[6];
    testData[0].body = "studentId int PRIMARY KEY,name varchar(15),gender varchar(1),age int";
    testData[0].instruction = "create";
    testData[0].condition = "null";
    testData[0].table = "Student";
    testData[1].body = "licenseNumber varchar(10),brand varchar(15),model varchar(15),type varchar(2),engineSize int";
    testData[1].instruction = "create";
    testData[1].condition = "null";
    testData[1].table = "Vehicle";
    testData[2].body = "10, 'John Smith', 'M', 22";
    testData[2].instruction = "insert";
    testData[2].condition = "null";
    testData[2].table = "Student";
    testData[3].body = "11, 'Hsu You-Ting', 'F', 23";
    testData[3].instruction = "insert";
    testData[3].condition = "null";
    testData[3].table = "Student";
*/

    DataBase* testDataBase = new DataBase("testDataBase");
    dataInput testData;
    Inst* inst = format_instruction("input.txt");
    for(;inst->next != NULL;)
    {
        testData.body = inst->body;
        testData.instruction = inst->instruction;
        testData.condition = inst->condition;
        testData.table = inst->table_name;
        testDataBase->inputData(&testData);
        //inst->print();
        //cout << endl;
        inst = inst->next;
    }
    cout<<endl;
    cout << "finish loop"<<endl;
    cout<<endl;

/*
    if(testDataBase->inputData(&testData[0])) cout << "create first table success" << endl;
    if(testDataBase->inputData(&testData[1])) cout << "create second table success" << endl;
    if(testDataBase->inputData(&testData[2])) cout << "insert first data success" << endl;
    if(testDataBase->inputData(&testData[3])) cout << "insert second data success" << endl;*/

    testDataBase->printAllTable();
    testDataBase->printTable("ARTICLE");
    testDataBase->printTable("COMMENT");
    testDataBase->printTable("LINKS");
    return 0;
}
