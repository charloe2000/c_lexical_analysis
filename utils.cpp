#include <iostream>
#include <fstream>
#include "utils.h"
#include "config.h"
using namespace std;

Record::Record() {

}

Record::Record(string s, string c) {
	symbol = s;
	content = c;
	if (c == ",") {
		content = "，";
	}
	pos = -1;
}
Record::Record(string s, string c, int p) {
	symbol = s;
	content = c;
	pos = p;
}

void Record::printRecord(ofstream* output, int *count) {
	//cout << "<" << symbol << ", " << content << ">" << endl;
	*output<< symbol << ", " << content << endl;
	for (int i = 0; i < 14;i++) {
		if (!symbol.compare(Symbol[i])) {
			(*(count+i))++;
			return;
		}
	}
}
void Record::printError(ofstream* output) {
	*output << "An error appears on line " << pos<<","<<content << endl;
}

Table::Table() {
	index = 0;
}

bool Table::insertTable(Record record) {
	/*if (searchTable(record.content))
		return false;
	else */if (index < MAX_RECORD_NUMBER) {
		records[index] = record;
		index++;
		return true;
	}
	else {
		throw "insertTable: out of MAX_RECORD_NUMBER";
		return false;
	}
}

/*bool Table::searchTable(string content) {
	for (int i = 0; i < index; i++) {
		if (records[i].content == content)
			return true;
	}
	return false;
}*/

void Table::printTable(ofstream* output, int *count) {
	for (int i = 0; i < index; i++) {
		records[i].printRecord(output,count);
	}
}
void Table::printError(ofstream* output) {
	for (int i = 0; i < index; i++) {
		records[i].printError(output);
	}
}

bool isKeyword(string buffer) {
	for (int i = 0; i < KEYWORD_NUMBER; i++) {
		if (buffer == KEYWORD_TABLE[i])
			return true;
	}
	return false;
}

bool isPunctuation(char ch) {
	for (int i = 0; i < PUNCTUATION_NUMBER; i++) {
		if (ch == PUNCTUATION_TABLE[i])
			return true;
	}
	return false;
}
char getch(ifstream* f, int* chnum, int* linenum) {
	char ch = f->get();
	(*chnum)++;
	if (ch == '\n')
		(*linenum)++;
	return ch;
}
