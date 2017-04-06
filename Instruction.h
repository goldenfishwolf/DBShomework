#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include <iostream>

class Inst
{
    public:
    Inst()
    {
        next = NULL;
    }

    void print()
    {
        std::cout<<"instruction is "<<instruction<<std::endl;
        std::cout<<"table_name is "<<table_name<<std::endl;
        std::cout<<"body is "<<body<<std::endl;
        std::cout<<"condition is "<<condition<<std::endl;
    }
    void clear_inst()
    {
        instruction = "";
        table_name = "";
        body = "";
        condition = "";
    }

    std::string instruction;
    std::string table_name;
    std::string body;
    std::string condition;
    Inst* next;
};

extern Inst* format_instruction(std::string in);

#endif
