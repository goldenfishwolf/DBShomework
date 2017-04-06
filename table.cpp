//
// Created by Administrator on 2017/3/13 0013.
//

#include "table.h"
//
// Created by Administrator on 2017/3/13 0013.
//
//structure input data


//class table, construct a table and manage data
//max attribute number is 4

//split string through given pattren
vector<std::string> splitWithStl(const std::string &str,const std::string &pattern)
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
}

    //create table
    bool
    Table::createTable(dataInput* data){

        tableName = data->table;
        vector<string> bodyAttributes = splitWithStl( data->body, ",");
        string attrAndName;
        //missing right parenthesis
        if(bodyAttributes.back() == "") {
            cout <<"missing right parenthesis !" <<endl;
            return false;
        }
        //parse each attribute
        for(auto t:bodyAttributes) {
            attributes[attrCount] = new attribute;
            vector<string> tempAttributes = splitWithStl(t, " ");

            //if size > 2, it indicates that the structure is " field type primary key"
            if (tempAttributes.size() > 2) {
                attributes[attrCount]->isKey = true;
                while (tempAttributes.size() > 2) tempAttributes.pop_back();
            } else attributes[attrCount]->isKey = false;

            //if type can be split by "(", it indicates that the type pattern is "type typelength"
            string typeIncludeLen = (tempAttributes.back());
            vector<string> type = splitWithStl(typeIncludeLen, "(");
            if (type.size() > 1) {
                attributes[attrCount]->typeLen = atoi(type.back().c_str());
                type.pop_back();
            }else attributes[attrCount]->typeLen = NULL;
            attributes[attrCount]->type = (type.back());

            type.clear();
            tempAttributes.pop_back();
            //last content of vector is field
            attributes[attrCount]->field = tempAttributes.back();
            tempAttributes.clear();

            attrCount++;

        }
        if(createValid()) return true;
        else return false;
    }

    bool
    Table::insert(dataInput* data){
       // cout <<"handle insert(in table insert func)" <<endl;
        //key is not null
        //condition insert
        attribute** newItem = new attribute*[attrCount+1];
        //for(int i = 0; i < attrCount+1;i++) newItem[i] = new attribute;
        //initiallize the node
        for (int i = 0; i < attrCount+1; i++) {
            newItem[i] = new attribute;
            newItem[i]->type = "null";
            newItem[i]->typeLen = NULL;
            newItem[i]->isKey = false;
            newItem[i]->content = "null";
        }
        newItem[attrCount]->type = "end";

        vector<string> body = splitWithStl(data->body, ",");

        if(data->condition != ""){
            vector<string> conditions = splitWithStl(data->condition, ",");

             while(!conditions.empty()) {
                 int validCount;
                for (int i = attrCount-1; i >=0; i--) {
                    if (attributes[i]->field == conditions.back() && insertAttrValid(attributes[i], body.back())) {
                        newItem[i]->type = attributes[i]->type;
                        newItem[i]->typeLen = attributes[i]->typeLen;
                        newItem[i]->isKey = attributes[i]->isKey;
                        newItem[i]->content = body.back();
                        body.pop_back();
                        break;
                    }else if(attributes[i]->field == conditions.back())
                        return false;
                    validCount = i;
                }
                 if(validCount == 0) {
                     cout <<"no such field: <" << conditions.back()<<">"<<endl;
                     return false;
                 }
             }
        }else{
            for(int i = attrCount -1 ; i>=0 ; i--){
                //cout << attributes[i]->type <<"<>"<<body.back()<<endl;
                if(insertAttrValid(attributes[i], body.back())){
                    newItem[i]->type = attributes[i]->type;
                    newItem[i]->typeLen = attributes[i]->typeLen;
                    newItem[i]->isKey = attributes[i]->isKey;
                    newItem[i]->content = body.back();
                    body.pop_back();
                }else
                    return false;

            }
        }
        //ensure key attribute is not null
        for(int i = 0; i < attrCount; i++){
            if(newItem[i]->isKey && newItem[i]->content == "null") {
                cout<<"error: try to insert item without key"<<endl;
                return false;
            }
        }

        //insert key
        if(!(tableTree->insert(newItem))) {
            return false;
        }
        return true;
    }
    //get table name, which is private

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

    //verify whether the input data is valid or not
    bool
    Table::insertAttrValid(attribute* a, string &b){
        if(a->type == "INT" && atoi(b.c_str()) == NULL) {
            if(b == "0") return true;
            cout <<"except <" <<a->type <<"> but input <"<<b<<">"<<endl;
            return false;
        }
        if(a->type == "VARCHAR" && b.size()-3 > a->typeLen) {
            cout << "'"<<b <<"': "<<endl;
            cout << "input varchar lager than limited size"<<endl;
            return false;
        }
        if(a->type == "CHAR" && b.size()-3 > a->typeLen) return false;
        //cout <<"type match" <<endl;
        return true;
    }

    //verify whether the create is valid or not
    bool
    Table::createValid(){
        for(int i = 0; i < attrCount; i++){
            if(attributes[i]->type == "INT") continue;
            if(attributes[i]->type == "CHAR") continue;
            if(attributes[i]->type == "VARCHAR") continue;
            cout << "type: <" << attributes[i]->type << "> is invalid !" <<endl;
            return false;
        }
        return true;
    }

//create a database
//max table number is 5

    bool
    DataBase::inputData(dataInput *data) {
       // cout <<"handle input data"<<endl;
        if (data->instruction == "create") {
            //cout<<"create table"<<endl;
            int tableFree;
            //create an empty table
            if(usedTable < MAX_TABLE) {
                for(tableFree = 0; table[tableFree]!= nullptr;tableFree++);
              //  cout <<"pick a free table space to create"<<endl;
            }
            else{
                cout << "error, too many tables" << endl;
                return false;
            }
            //c检查重名table
            for(int i = 0; i < MAX_TABLE; i++){
                //if(table[i] != nullptr) cout << table[i]->getName() << " input table: "<<data->table<<endl;
                if(table[i] != nullptr && table[i]->getName() == data->table) {
                    cout <<"create failed, exist same name table"<<endl;
                    return false;
                }
            }
           // cout <<"table name valid"<<endl;
            table[tableFree] = new Table();
            //modify and verify the table
            if(table[tableFree]->createTable(data) )  {
               // cout <<"create successful"<<endl;
                usedTable++;
                return true;
            }
            else {
                delete table[tableFree];
                table[tableFree] = nullptr;
                return false;
            }
        } else if (data->instruction == "insert") {
            //cout << "insert data"<<endl;
            for(int i = 0; i <=MAX_TABLE; i++){
                if(table[i] != nullptr) {
                    if (table[i]->getName() == data->table ) {
                        //cout <<"exist such table"<<endl;
                        if(table[i]->insert(data)) return true;
                        else return false;
                    }
                }
            }
            cout <<"fail to insert: no such table" <<endl;
            return false;
        } else if (data->instruction == "modify") {
            return false;
        } else if (data->instruction == "remove") {
            return false;
        }
        cout << "invalid instruction"<<endl;
        return false;
    };

    void
    DataBase::printAllTable() {
        cout<<dataBaseName<<endl;
        for(int i = 0; i<MAX_TABLE; i++){
            if(table[i]!= nullptr){
                cout <<"prepare print table" <<endl;
                table[i]->printAttribute();
            }
        }
    }
    void
    Table::printAttribute() {
        for(int i = 0; i < attrCount; i++){
            cout << attributes[i]->field<<" : " <<attributes[i]->type;
            if(attributes[i]->typeLen!=NULL) cout << "(" <<attributes[i]->typeLen <<")";
            cout <<" //" <<attributes[i]->isKey <<endl;
        }
    }

    void
    DataBase::printTable(string tableName){
        int i = 0;
        for(i = 0; i < MAX_TABLE;i++){
            if(table[i]!= nullptr)
            if(table[i]->getName() == tableName) {
                table[i]->printContent();
                break;
            }
        }
        if(i == MAX_TABLE) cout <<"no such table" <<endl;
    }

    void
    Table::printContent() {
        tableTree->display();
    }

//DATABASE_MID_TABLE_H
