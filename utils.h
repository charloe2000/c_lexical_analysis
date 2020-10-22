#pragma once
#include <iostream>
#include <fstream>
#include "config.h"
using namespace std;

//记号表中的一条记录
class Record {
public:
	string symbol;
	string content;
	int pos;


	Record();
	Record(string s, string c);
	Record(string s, string c, int pos);

	void printRecord(ofstream* output, int *count);
	void printError(ofstream* output);
};

//记号表
class Table {
private:
	Record records[MAX_RECORD_NUMBER];
	int index;

	//搜索记号表
	/*bool searchTable(string content);*/

public:
	Table();

	//一条记录插入记号表前，搜索记号表中是否已有该记号
	bool insertTable(Record record);
	//打印记号表中的所有记录
	void printTable(ofstream* output, int *count);
	void printError(ofstream* output);
};

bool isKeyword(string buffer);

bool isPunctuation(char ch);

char getch(ifstream* f, int* chnum, int* linenum);
