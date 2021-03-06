#include "Instruction.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

#define TABLE_MAX_NAME_LENGTH 40
using namespace std;

char* deal_space(char* input, int length)
{
    char* return_str = new char[length];
    int varchar_count = 0;
    int j = 0;
    for(int i = 0;i < length; i++)
    {
        if(input[i] == '\'')
        {
            varchar_count++;
            if(varchar_count == 2)
            {
                varchar_count = 0;
            }
            return_str[j] = input[i];
            j++;
        }
        else if(input[i] == '(')
        {
            {
                int k = 1;
                for(;(input[i+k] == ' ' || input[i+k] == '\n') && i+k < length; k++);
                return_str[j] = '(';
                i+=k-1;
                j++;
            }
        }
        else if(input[i] == ')')
        {
            {
                int k = 1;
                for(;(input[i+k] == ' ' || input[i+k] == '\n') && i+k < length; k++);
                return_str[j] = ')';
                i+=k-1;
                j++;
            }
        }
        else if(input[i] == ',')
        {
            {
                int k = 1;
                for(;(input[i+k] == ' ' || input[i+k] == '\n') && i+k < length; k++);
                return_str[j] = ',';
                i+=k-1;
                j++;
            }
        }
        else if( (input[i] == ' ' || input[i] == '\n') && varchar_count == 0)
        {
            {
                int k = 0;
                for(;(input[i+k] == ' ' || input[i+k] == '\n') && i+k < length; k++);
                if(input[i+k] == '(')
                {
                    k++;
                    for(;(input[i+k] == ' ' || input[i+k] == '\n') && i+k < length; k++);
                    return_str[j] = '(';
                    i+=k-1;
                }
                else if(input[i+k] == ')')
                {
                    k++;
                    for(;(input[i+k] == ' ' || input[i+k] == '\n') && i+k < length; k++);
                    return_str[j] = ')';
                    i+=k-1;
                }
                else if(input[i+k] == ',')
                {
                    k++;
                    for(;(input[i+k] == ' ' || input[i+k] == '\n') && i+k < length; k++);
                    return_str[j] = ',';
                    i+=k-1;
                }
                else
                {
                    return_str[j] = ' ';
                    i+=k-1;
                }
                j++;

            }
        }
        else
        {
            if(varchar_count > 0)
            {
                return_str[j] = input[i];
            }
            else
            {
                return_str[j] = toupper(input[i]);
            }
            j++;
        }
    }
    return_str[j] = '\0';
    return return_str;
}

bool parser(char* input,int length,Inst* next)
{
    int i = 0;
    if(input[0] == ' ')
    {
        i++;
    }
    if(input[i] == 'C' && input[i+1] == 'R' && input[i+2] == 'E' && input[i+3] == 'A' && input[i+4] == 'T' && input[i+5] == 'E'
        && input[i+6] == ' ' && input[i+7] == 'T' && input[i+8] == 'A' && input[i+9] == 'B' && input[i+10] == 'L'
        && input[i+11] == 'E'  && input[i+12] == ' ')
    {
        i += 13;
        next->instruction = "create";
        {
            char temp[TABLE_MAX_NAME_LENGTH+1];
            int j = 0;
            for(;input[i] != '(' && input[i] != ' ' ; i++,j++)
            {
                if(j > TABLE_MAX_NAME_LENGTH)
                {
                    j = -1;
                    break;
                }
                temp[j] = input[i];
            }
	    if(input[i] == ' ')
	    {
		cout<<"expect ( !\n";
                return false;
	    }
            if(j != -1)
            {
                temp[j] = '\0';
                next->table_name.assign(temp);
            }
            else
            {
                cout<<"the table name's length is over 40!\n";
                return false;
            }
        }
        {
            int left_num = 1;
            int right_num = 0;
            int stop_num = 0;
            i++;
            for(;i < length;i++)
            {
                if(input[i] == '\'')
                {
                    stop_num++;
                }
                if(stop_num > 0 )
                {
                    if(stop_num == 2)
                    {
                        stop_num = 0;
                    }
                    next->body += input[i];
                    continue;
                }
                if(input[i] == '(')
                {
                    left_num++;
                    next->body += input[i];
                }
                else if(input[i] == ')')
                {
                    right_num++;
                    next->body += input[i];
                }
                else
                {
                    next->body += input[i];
                }
            }
            if(left_num == right_num && stop_num == 0)
            {
                next->body.resize(next->body.size()-1);
                return true;
            }
            else if (left_num == right_num)
            {
                cout<<"expect ' !\n";
                return false;
            }
            else if (left_num > right_num)
            {
                cout<<"expect ) !\n";
                return false;
            }
            else
            {
                cout<<"expect ( !\n";
                return false;
            }
        }
    }
    else if(input[i] == 'I' && input[i+1] == 'N' && input[i+2] == 'S' && input[i+3] == 'E' && input[i+4] == 'R' && input[i+5] == 'T'
        && input[i+6] == ' ' && input[i+7] == 'I' && input[i+8] == 'N' && input[i+9] == 'T' && input[i+10] == 'O'
        && input[i+11] == ' ')
    {
        i += 12;
        next->instruction = "insert";
        {
            char temp[TABLE_MAX_NAME_LENGTH+1];
            int j = 0;
            for(;input[i] != '(' && input[i] != ' '; i++,j++)
            {
                if(j > TABLE_MAX_NAME_LENGTH)
                {
                    j = -1;
                    break;
                }
                temp[j] = input[i];
            }
            if(j != -1)
            {
                temp[j] = '\0';
                next->table_name.assign(temp);
            }
            else
            {
                cout<<"the table name's length is over 40!\n";
                return false;
            }
        }
        if(input[i] == '(')
        {
            i++;
            for(;input[i] != ')';i++)
            {
                if(input[i] == '\'' || i == length - 9)
                {
                    cout<<"expect ) !\n";
                    return false;
                }
                next->condition += input[i];
            }
            i++;
            if(input[i] == ' ')
            {
                i++;
            }
            if(input[i] == 'V' && input[i+1] == 'A' && input[i+2] == 'L' && input[i+3] == 'U' && input[i+4] == 'E'
               && input[i+5] == 'S')
            {
                i += 6;
                if(input[i] == '(')
                {
                    int left_num = 1;
                    int right_num = 0;
                    int stop_num = 0;
                    i++;
                    for(;i < length;i++)
                    {
                        if(input[i] == '\'')
                        {
                            stop_num++;
                        }
                        if(stop_num > 0 )
                        {
                            if(stop_num == 2)
                            {
                                stop_num = 0;
                            }
                            next->body += input[i];
                            continue;
                        }
                        if(input[i] == '(')
                        {
                            left_num++;
                            next->body += input[i];
                        }
                        else if(input[i] == ')')
                        {
                            right_num++;
                            next->body += input[i];
                        }
                        else
                        {
                            next->body += input[i];
                        }
                    }
                    if(left_num == right_num && stop_num == 0)
                    {
                        next->body.resize(next->body.size()-1);
                        return true;
                    }
                    else if (left_num == right_num)
                    {
                        cout<<"expect ' !\n";
                        return false;
                    }
                    else if (left_num > right_num)
                    {
                        cout<<"expect ) !\n";
                        return false;
                    }
                    else
                    {
                        cout<<"expect ( !\n";
                        return false;
                    }
                }
                else
                {
                    cout<<"expect ( !\n";
                    return false;
                }
            }
            else
            {
                cout<<"expect VALUES !\n";
                return false;
            }
        }
        else if(input[i] == ' ' && input[i+1] == 'V' && input[i+2] == 'A' && input[i+3] == 'L' && input[i+4] == 'U'
                && input[i+5] == 'E' && input[i+6] == 'S')
        {
            i += 7;
            if(input[i] == '(')
            {
                int left_num = 1;
                int right_num = 0;
                int stop_num = 0;
                i++;
                for(;i < length;i++)
                {
                    if(input[i] == '\'')
                    {
                        stop_num++;
                    }
                    if(stop_num > 0 )
                    {
                        if(stop_num == 2)
                        {
                            stop_num = 0;
                        }
                        next->body += input[i];
                        continue;
                    }
                    if(input[i] == '(')
                    {
                        left_num++;
                        next->body += input[i];
                    }
                    else if(input[i] == ')')
                    {
                        right_num++;
                        next->body += input[i];
                    }
                    else
                    {
                        next->body += input[i];
                    }
                }
                if(left_num == right_num && stop_num == 0)
                {
                    next->body.resize(next->body.size()-1);
                    return true;
                }
                else if (left_num == right_num)
                {
                    cout<<"expect ' !\n";
                    return false;
                }
                else if (left_num > right_num)
                {
                    cout<<"expect ) !\n";
                    return false;
                }
                else
                {
                    cout<<"expect ( !\n";
                    return false;
                }
            }
            else
            {
                cout<<"expect ( !\n";
                return false;
            }
        }
        else
        {
            cout<<"invalid instruction!!\n";
            return false;
        }
    }
    else if(input[i] == 'S' && input[i+1] == 'E' && input[i+2] == 'L' && input[i+3] == 'E' && input[i+4] == 'C' && input[i+5] == 'T'
        && input[i+6] == ' ')
    {
        i += 7;
        next->instruction = "select";
        for(;i < length;)
        {
            if(input[i] == ' ' && input[i+1] == 'F' && input[i+2] == 'R' && input[i+3] == 'O' && input[i+4] == 'M' && input[i+5] == ' ')
            {
                i += 6;
                break;
            }
            next->body += input[i];
            i++;
        }

        for(;i < length;)
        {
            if(input[i] == ' ' && input[i+1] == 'W' && input[i+2] == 'H' && input[i+3] == 'E' && input[i+4] == 'R' && input[i+5] == 'E' && input[i+6] == ' ')
            {
                i += 7;
                break;
            }
            if(input[i] == 'A' && input[i+1] == 'S' && input[i+2] == ' ')
            {
                i += 3;
                continue;
            }
            next->table_name += input[i];
            i++;
        }

        for(;i < length;)
        {
            next->condition += input[i];
            i++;
        }

        {
            bool isalias = false;
            string tem_alias = "";
            string tem_alias_name = "";
            size_t tem_pos = 0;
            for(int k = 0; k <= (int)next->table_name.size();)
            {
                if(k == (int)next->table_name.size())
                {
                    isalias = true;
                }
                else if(next->table_name.c_str()[k] == ' ')
                {
                    k += 1;
                    isalias = true;
                    continue;
                }
                if(isalias && ( k == (int)next->table_name.size() || next->table_name.c_str()[k] == ',') )
                {
                    isalias = false;
                    for(size_t j = 0;j < string::npos;)
                    {
                        if(j)
                        {
                            j = next->body.find(tem_alias + ".",j+1);
                        }
                        else
                        {
                            j = next->body.find(tem_alias + ".");
                        }

                        if(j == string::npos)
                        {
                            break;
                        }
                        else
                        {
                            if(j == 0)
                            {
                                next->body.replace(0,tem_alias.size(),tem_alias_name);
                            }
                            else
                            {
                                if(next->body.c_str()[j-1] == ',')
                                {
                                    next->body.replace(j,tem_alias.size(),tem_alias_name);
                                }
                            }
                        }
                    }
                    for(size_t j = 0;j < string::npos;)
                    {
                        if(j)
                        {
                            j = next->condition.find(tem_alias + ".",j+1);
                        }
                        else
                        {
                            j = next->condition.find(tem_alias + ".");
                        }
                        if(j != string::npos)
                        {
                            if(j == 0)
                            {
                                next->condition.replace(0,tem_alias.size(),tem_alias_name);
                            }
                            else
                            {
                                if(next->condition.c_str()[j-1] == ',' || next->condition.c_str()[j-1] == ' ')
                                {
                                    next->condition.replace(j,tem_alias.size(),tem_alias_name);
                                }
                            }
                        }
                    }
                    tem_pos = next->table_name.find(" " + tem_alias);
                    if(tem_pos != string::npos)
                    {
                        next->table_name.replace(tem_pos,tem_alias.size()+1,"");
                    }
                    else
                    {
                        cout<<"can't find the alias!\n";
                    }

                    tem_alias = "";
                    tem_alias_name = "";
                }
                else if(isalias)
                {
                    tem_alias += next->table_name.c_str()[k];

                }
                else
                {
                    tem_alias_name += next->table_name.c_str()[k];
                }

                k++;
            }
        }

        return true;
    }
    else
    {
        cout<<"invalid instruction!\n";
        return false;
    }
}



Inst* format_instruction(string in)
{
    ifstream input;
    input.open(in,fstream::in);
    if(!input.is_open())
    {
        cout<<"open file error!\n";
    }
    string line;
    char* tem;
    Inst* start = new Inst;
    Inst* next = start;
    while(getline(input,line,';'))
    {
        tem = deal_space((char*)line.c_str(),(int)line.size());
        cout<<tem<<endl;
        if(parser(tem,(int)strlen(tem),next))
        {
            next-> print();
            next->next = new Inst;
            next = next->next;
        }
        else
        {
            next->clear_inst();
        }
    }

    return start;
}
