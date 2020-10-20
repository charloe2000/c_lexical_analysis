#include <iostream>
#include "utils.h"
#include "config.h"
using namespace std;

Record::Record(){

}

Record::Record(string s, string c){
    symbol = s;
    content = c;
}

void Record::printRecord(){
    cout << "<" << symbol << ", " << content << ">" << endl;
}

Table::Table(){
    index = 0;
}

bool Table::insertTable(Record record){
    if(searchTable(record.content))
        return false;
    else if (index < MAX_RECORD_NUMBER){ 
        records[index] = record;
        index++;
        return true;
    }
    else{
        throw "insertTable: out of MAX_RECORD_NUMBER";
        return false;
    }
}

bool Table::searchTable(string content){
    for (int i = 0; i < index; i++){
        if(records[i].content == content)
            return true;
    }
    return false;
}

void Table::printTable(){
    for (int i = 0; i < index; i++){
        records[i].printRecord();
    }
}
