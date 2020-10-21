#pragma once
#include <iostream>
#include "config.h"
;using namespace std;

//记号表中的一条记录
class Record{
public:
    string symbol;
    string content;


    Record();
    Record(string s, string c);

    void printRecord();
};

//记号表
class Table{
private:
    Record records[MAX_RECORD_NUMBER];
    int index;

    //搜索记号表
    bool searchTable(string content);

public:
    Table();

    //一条记录插入记号表前，搜索记号表中是否已有该记号
    bool insertTable(Record record);
    //打印记号表中的所有记录
    void printTable();
};

bool isKeyword(string buffer);

bool isPunctuation(char ch);