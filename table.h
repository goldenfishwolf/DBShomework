//
// Created by Administrator on 2017/3/13 0013.
//
#include <iostream>
#include <string>
#include <vector>
#include "cbtree.h"
#include <cstdlib>

using namespace std;
#define ATTRIBUTE
#ifndef DATABASE_MID_TABLE_H
#define DATABASE_MID_TABLE_H


/*
//operator overload
bool operator==(attribute** const &lhs, attribute** const &rhs){
    bool hasKey = false;
    for(int i = 0; i < MAX_ATTRIBUTE; i++){
        if(lhs[i]->isKey) hasKey = true;
        if(lhs[i]->isKey && lhs[i]->content != rhs[i]->content) return false;
    }
    if(hasKey) return true;
    for(int i = 0; i < MAX_ATTRIBUTE; i++){
        if(lhs[i]->content != rhs[i]->content) return false;
    }
    return true;
}

bool operator<(attribute** const &lhs, attribute** const &rhs){
    bool hasKey = false;
    for(int i = 0; i < MAX_ATTRIBUTE; i++){
        if(lhs[i]->isKey) hasKey = true;
        if(lhs[i]->isKey && lhs[i]->content > rhs[i]->content) return false;
        if(lhs[i]->isKey && lhs[i]->content < rhs[i]->content) return true;
    }
    if(hasKey) return false;
    for(int i = 0; i < MAX_ATTRIBUTE; i++){
        if(lhs[i]->content > rhs[i]->content) return false;
        if(lhs[i]->content < rhs[i]->content) return true;
    }
    return false;
}

bool operator>(attribute** const &lhs,attribute**  const &rhs){
    bool hasKey = false;
    for(int i = 0; i < MAX_ATTRIBUTE; i++){
        if(lhs[i]->isKey) hasKey = true;
        if(lhs[i]->isKey && lhs[i]->content < rhs[i]->content) return false;
        if(lhs[i]->isKey && lhs[i]->content > rhs[i]->content) return true;
    }
    if(hasKey) return false;
    for(int i = 0; i < MAX_ATTRIBUTE; i++){
        if(lhs[i]->content < rhs[i]->content) return false;
        if(lhs[i]->content > rhs[i]->content) return true;
    }
    return false;
}

bool operator<=(attribute** const &lhs, attribute** const &rhs){
    bool hasKey = false;
    for(int i = 0; i < MAX_ATTRIBUTE; i++){
        if(lhs[i]->isKey) hasKey = true;
        if(lhs[i]->isKey && lhs[i]->content > rhs[i]->content) return false;
        if(lhs[i]->isKey && lhs[i]->content < rhs[i]->content) return true;
    }
    if(hasKey) return true;
    for(int i = 0; i < MAX_ATTRIBUTE; i++){
        if(lhs[i]->content > rhs[i]->content) return false;
        if(lhs[i]->content < rhs[i]->content) return true;
    }
    return true;
}

bool operator>=(attribute** const &lhs, attribute** const &rhs){
    bool hasKey = false;
    for(int i = 0; i < MAX_ATTRIBUTE; i++){
        if(lhs[i]->isKey) hasKey = true;
        if(lhs[i]->isKey && lhs[i]->content < rhs[i]->content) return false;
        if(lhs[i]->isKey && lhs[i]->content > rhs[i]->content) return true;
    }
    if(hasKey) return true;
    for(int i = 0; i < MAX_ATTRIBUTE; i++){
        if(lhs[i]->content < rhs[i]->content) return false;
        if(lhs[i]->content > rhs[i]->content) return true;
    }
    return true;
}*/

//structure input data
typedef struct _data_{
    string table;
    string body;
    string condition;
    string instruction;
    //bool isvalid;
   // _data_* next;
}dataInput;



//overload cout





//split string through given pattren
/*vector<std::string> splitWithStl(const std::string &str,const std::string &pattern)
{
    vector<std::string> resVec;

    if ("" == str)
    {
        return resVec;
    }

    std::string strs = str + pattern;

    size_t pos = strs.find(pattern);
    size_t size = strs.size();

    while (pos != std::string::npos)
    {
        std::string x = strs.substr(0,pos);
        resVec.push_back(x);
        strs = strs.substr(pos+1,size);
        pos = strs.find(pattern);
    }

    return resVec;
}*/

//class table, construct a table and manage data
//max attribute number is 4
class Table{
private:
    string tableName;
    attribute** attributes;
    CBTree *tableTree;
    //CBTree<attribute**> *tableTree;
    int attrCount;
public:
    Table() {
        attributes = new attribute*[MAX_ATTRIBUTE];
        tableTree = new CBTree;
        attrCount = 0;
    }

    //create table
    bool createTable(dataInput* data);

    bool insert(dataInput* data);
    //get table name, which is private
    string getName() {
        return tableName;
    }

    /*bool modify(dataInput* data){
        //key has in the CBTree
        if(tableTree->contain(nullptr)){
            //modify
        }else
            return false;
    };
    bool remove(dataInput* data){
        if(tableTree->remove(NULL)) return true;
        else return false;
    }*/

    void printAttribute(void);
    void printContent();
private:

    //verify whether the input data is valid or not
    bool insertAttrValid(attribute* a, string &b);

    //verify whether the create is valid or not
    bool createValid();

};
//create a database
//max table number is 5
class DataBase {
private:
    Table* table[MAX_TABLE];
    string dataBaseName;
    int usedTable;
public:
    DataBase(string name) {
        dataBaseName = name;
        usedTable = 0;
        for(int i = 0; i < MAX_TABLE; i++){
            table[i] = nullptr;
        }
    };


//handle the data input
    bool inputData(dataInput *data);
    void printAllTable();
    void printTable(string tableName);
private:

};






#endif //DATABASE_MID_TABLE_H
