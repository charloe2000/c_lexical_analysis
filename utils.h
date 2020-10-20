#pragma once
#include <iostream>
#include "config.h"
using namespace std;

class Record{
public:
    string symbol;
    string content;


    Record();
    Record(string s, string c);

    void printRecord();
};

class Table{
private:
    Record records[MAX_RECORD_NUMBER];
    int index;

    bool searchTable(string content);

public:
    Table();

    bool insertTable(Record record);
    void printTable();
};