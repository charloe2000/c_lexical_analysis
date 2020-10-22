#include "config.h"
#include "utils.h"
#include <fstream>
#include <string>
using namespace std;
int main() {
	//开始状态
	State state = BEGIN;
	//记号表
	Table table;
	Table errTable;
	//当前字符
	char ch;
	//当前词
	string buffer;
	int count[16] = {};
	ifstream fin;
	fin.open("code.c");
	while (isspace(ch = getch(&fin,&count[14],&count[15])))
		count[15]++;
	do {
		switch (state) {
			//开始状态
		case BEGIN: {
			//进入开始状态时ch保证是不为空且不为空格的
			//把字符加入到当前词
			buffer += ch;

			if (isalpha(ch) || ch == '_') state = ID_KEYWORD_0;	// 标识符或关键字
			else if (isPunctuation(ch))	state = PUNCTUATION_0;	//标点符号	
			else if (ch == '#') state = INCLUDE_0; //#include
			else if (isdigit(ch)) state = DIGIT_0;// 数
			else if (ch == '.') state = DIGIT_1;// 数
			else if (ch == '+') state = ARITH_0;// +
			else if (ch == '-') state = ARITH_1;// -
			else if (ch == '*') state = ARITH_2;// *
			else if (ch == '%') state = ARITH_3;// %
			else if (ch == '>') state = RELATION_0;// >
			else if (ch == '=') state = ASSIGN_0; // =
			else if (ch == '<') state = RELATION_1;// <
			else if (ch == '&') state = LOGICAL_0;// &
			else if (ch == '|') state = LOGICAL_1;// |
			else if (ch == '!') state = LOGICAL_2;// !
			else if (ch == '\'') state = SINGLE_QUETO_0;// '
			else if (ch == '\"') state = DOUBLE_QUETO_0;// "
			else if (ch == '/') state = COMMENT_0; // /

			else state = ERROR;//词法错误
			break;
		}
		//包含语句
		case INCLUDE_0: {
			ch = getch(&fin,&count[14],&count[15]);
			buffer += ch;

			if (isalpha(ch)) {
				state = INCLUDE_1;
			}
			else {
				state = ERROR;
			}
			break;
		}
		case INCLUDE_1: {
			ch = getch(&fin,&count[14],&count[15]);
			if (isalpha(ch)) {
				buffer += ch;
			}
			else {
				if (buffer == "#include") {
					buffer += ch;
					state = INCLUDE_2;
				}
				else {
					state = ERROR;
				}
			}
			break;
		}
		case INCLUDE_2: {
			ch = getch(&fin,&count[14],&count[15]);
			if (!isspace(ch)) {
				buffer += ch;
				state = INCLUDE_2;
			}
			else {
				table.insertTable(Record(INCLUDE, buffer));
				state = END;
			}
			break;
		}

		//标识符或关键字的第一个状态
		case ID_KEYWORD_0: {
			ch = getch(&fin,&count[14],&count[15]);

			if (isalpha(ch) || isdigit(ch) || ch == '_') {
				buffer += ch;
			}
			else {
				if (isKeyword(buffer)) {
					table.insertTable(Record(KEYWORD, buffer));
				}
				else {
					table.insertTable(Record(ID, buffer));
				}
				state = END;
			}
			break;
		}

		//数
		case DIGIT_0: {
			ch = getch(&fin,&count[14],&count[15]);

			if (isdigit(ch)) {
				buffer += ch;
				//state = DIGIT_0;
			}
			else if (ch == '.') {
				buffer += ch;
				state = DIGIT_2;
			}
			else if (ch == 'e' || ch == 'E') {
				buffer += ch;
				state = DIGIT_3;
			}
			else if (isalpha(ch) || ch == '_') {
				buffer += ch;
				state = ERROR;
			}
			else {
				table.insertTable(Record(INT, buffer));
				state = END;
			}
			break;
		}
		case DIGIT_1: {
			ch = getch(&fin,&count[14],&count[15]);
			buffer += ch;
			if (isdigit(ch)) {
				state = DIGIT_2;
			}
			else {
				state = ERROR;
			}
			break;
		}
		case DIGIT_2: {
			ch = getch(&fin,&count[14],&count[15]);

			if (isdigit(ch)) {
				buffer += ch;
				//state = DIGIT_2;
			}
			else if (ch == 'e' || ch == 'E') {
				buffer += ch;
				state = DIGIT_3;
			}
			else if (isalpha(ch) || ch == '_') {
				buffer += ch;
				state = ERROR;
			}
			else {
				table.insertTable(Record(DOUBLE, buffer));
				state = END;
			}
			break;
		}
		case DIGIT_3: {
			ch = getch(&fin,&count[14],&count[15]);
			buffer += ch;
			if (isdigit(ch)) {
				state = DIGIT_4;
			}
			else if (ch == '+' || ch == '-') {
				state = DIGIT_5;
			}
			else {
				state = ERROR;
			}
			break;
		}
		case DIGIT_4: {
			ch = getch(&fin,&count[14],&count[15]);

			if (isdigit(ch)) {
				buffer += ch;
				//state = DIGIT_4;
			}
			else if (isalpha(ch) || ch == '_') {
				buffer += ch;
				state = ERROR;
			}
			else {
				table.insertTable(Record(DOUBLE, buffer));
				state = END;
			}
			break;
		}
		case DIGIT_5: {
			ch = getch(&fin,&count[14],&count[15]);
			buffer += ch;
			if (isdigit(ch)) {
				state = DIGIT_4;
			}
			else {
				state = ERROR;
			}
			break;
		}

		//赋值运算符：= or 关系运算符： ==
		case ASSIGN_0: {
			ch = getch(&fin,&count[14],&count[15]);

			if (ch == '=') {
				buffer += ch;
				table.insertTable(Record(RELATION_OP, buffer));
				state = END;
				ch = getch(&fin,&count[14],&count[15]);
			}
			else {
				table.insertTable(Record(ASSIGN_OP, buffer));
				state = END;
			}
			break;
		}

		//关系运算符： >, >=, >>
		case RELATION_0: {
			ch = getch(&fin,&count[14],&count[15]);

			if (ch == '=') {
				buffer += ch;
				table.insertTable(Record(RELATION_OP, buffer));
				state = END;
				ch = getch(&fin,&count[14],&count[15]);
			}
			else if (ch == '>') {
				buffer += ch;
				table.insertTable(Record(RELATION_OP, buffer));
				state = END;
				ch = getch(&fin,&count[14],&count[15]);
			}
			else {
				table.insertTable(Record(RELATION_OP, buffer));
				state = END;
			}
			break;
		}
		//关系运算符： <, <=, <<
		case RELATION_1: {
			ch = getch(&fin,&count[14],&count[15]);

			if (ch == '=') {
				buffer += ch;
				table.insertTable(Record(RELATION_OP, buffer));
				state = END;
				ch = getch(&fin,&count[14],&count[15]);
			}
			else if (ch == '<') {
				buffer += ch;
				table.insertTable(Record(RELATION_OP, buffer));
				state = END;
				ch = getch(&fin,&count[14],&count[15]);
			}
			else {
				table.insertTable(Record(RELATION_OP, buffer));
				state = END;
			}
			break;
		}

		//逻辑运算符: &&
		case LOGICAL_0: {
			ch = getch(&fin,&count[14],&count[15]);
			buffer += ch;

			if (ch == '&') {
				table.insertTable(Record(LOGICAL_OP, buffer));
				state = END;
				ch = getch(&fin,&count[14],&count[15]);
			}
			else {
				state = ERROR;
			}
			break;
		}
		//逻辑运算符: ||
		case LOGICAL_1: {
			ch = getch(&fin,&count[14],&count[15]);
			buffer += ch;

			if (ch == '|') {
				table.insertTable(Record(LOGICAL_OP, buffer));
				state = END;
				ch = getch(&fin,&count[14],&count[15]);
			}
			else {
				state = ERROR;
			}
			break;
		}
		//逻辑运算符: ! or 关系运算符: !=
		case LOGICAL_2: {
			ch = getch(&fin,&count[14],&count[15]);
			if (ch == '=') {
				buffer += ch;
				table.insertTable(Record(RELATION_OP, buffer));
				state = END;
				ch = getch(&fin,&count[14],&count[15]);
			}
			else {
				table.insertTable(Record(LOGICAL_OP, buffer));
				state = END;
			}
			break;
		}

		//标点符号
		case PUNCTUATION_0: {
			ch = getch(&fin,&count[14],&count[15]);

			table.insertTable(Record(PUNCTUATION, buffer));
			state = END;
			break;
		}

		//单引号
		case SINGLE_QUETO_0: {
			ch = getch(&fin,&count[14],&count[15]);
			buffer += ch;

			state = SINGLE_QUETO_1;
			break;
		}
		case SINGLE_QUETO_1: {
			ch = getch(&fin,&count[14],&count[15]);
			buffer += ch;
			if (ch == '\'') {
				state = SINGLE_QUETO_2;
			}
			else {
				state = ERROR;
			}
			break;
		}
		case SINGLE_QUETO_2: {
			ch = getch(&fin,&count[14],&count[15]);
			if (isspace(ch) || isPunctuation(ch)) {
				table.insertTable(Record(CHAR, buffer));
				state = END;
			}
			else {
				buffer += ch;
				state = ERROR;
			}
			break;
		}

		//双引号
		case DOUBLE_QUETO_0: {
			ch = getch(&fin,&count[14],&count[15]);
			buffer += ch;

			if (ch == '\"') {
				state = DOUBLE_QUETO_2;
			}
			else {
				state = DOUBLE_QUETO_1;
			}
			break;
		}
		case DOUBLE_QUETO_1: {
			ch = getch(&fin,&count[14],&count[15]);
			buffer += ch;

			if (ch == '\"') {
				state = DOUBLE_QUETO_2;
			}
			else {
				state = DOUBLE_QUETO_1;
			}
			break;
		}
		case DOUBLE_QUETO_2: {
			ch = getch(&fin,&count[14],&count[15]);
			if (isspace(ch) || isPunctuation(ch)) {
				table.insertTable(Record(STRING, buffer));
				state = END;
			}
			else {
				buffer += ch;
				state = ERROR;
			}
			break;
		}

		//注释://
		case COMMENT_0: {
			ch = getch(&fin,&count[14],&count[15]);

			if (ch == '/') {
				buffer += ch;
				state = COMMENT_1;
			}
			else if (ch == '*') {
				buffer += ch;
				state = COMMENT_2;
			}
			else if (ch == '=') {
				buffer += ch;
				table.insertTable(Record(ARITH_OP, buffer));
				state = END;
			}
			else {
				table.insertTable(Record(ARITH_OP, buffer));
				state = END;
			}
			break;
		}
		case COMMENT_1: {
			ch = getch(&fin,&count[14],&count[15]);

			if (ch == '\n') {
				table.insertTable(Record(COMMENT, buffer));
				state = END;
			}
			else {
				buffer += ch;
			}
			break;
		}
		//注释:/*
		case COMMENT_2: {
			ch = getch(&fin,&count[14],&count[15]);
			buffer += ch;

			if (ch == '*') {
				state = COMMENT_3;
			}
			else if (ch == EOF) {
				state = ERROR;
			}
			break;
		}
		case COMMENT_3: {
			ch = getch(&fin,&count[14],&count[15]);
			buffer += ch;

			if (ch == '/') {
				table.insertTable(Record(COMMENT, buffer));
				state = END;
				ch = getch(&fin,&count[14],&count[15]);
			}
			else if (ch == EOF) {
				state = ERROR;
			}
			else {
				state = COMMENT_2;
			}
			break;
		}
		// +
		case ARITH_0: {
			ch = getch(&fin,&count[14],&count[15]);

			if (ch == '+' || ch == '=') {
				buffer += ch;
				table.insertTable(Record(ARITH_OP, buffer));
				ch = getch(&fin,&count[14],&count[15]);
				state = END;
			}
			else {
				table.insertTable(Record(ARITH_OP, buffer));
				state = END;
			}
			break;
		}
		// -
		case ARITH_1: {
			ch = getch(&fin,&count[14],&count[15]);

			if (ch == '-' || ch == '=') {
				buffer += ch;
				table.insertTable(Record(ARITH_OP, buffer));
				ch = getch(&fin,&count[14],&count[15]);
				state = END;
			}
			else {
				table.insertTable(Record(ARITH_OP, buffer));
				state = END;
			}
			break;
		}

		// *
		case ARITH_2: {
			ch = getch(&fin,&count[14],&count[15]);

			if (ch == '=') {
				buffer += ch;
				table.insertTable(Record(ARITH_OP, buffer));
				ch = getch(&fin,&count[14],&count[15]);
				state = END;
			}
			else {
				table.insertTable(Record(ARITH_OP, buffer));
				state = END;
			}
			break;
		}
		// %
		case ARITH_3: {
			ch = getch(&fin,&count[14],&count[15]);

			if (ch == '=') {
				buffer += ch;
				table.insertTable(Record(ARITH_OP, buffer));
				ch = getch(&fin,&count[14],&count[15]);
				state = END;
			}
			else {
				table.insertTable(Record(ARITH_OP, buffer));
				state = END;
			}
			break;
		}
		//读完一个词后，进入END状态。
		//进入END状态时，一定是ch当前在下一个词开头或为空格或为EOF
		case END: {
			if (isspace(ch)) {
				while (isspace(ch = getch(&fin,&count[14],&count[15])));
			}
			buffer = "";
			state = BEGIN;
			break;
		}

		//遇到无法解析的词法
		case ERROR: {
			//如果遇到无法识别的词,把该词剩余字符读取完毕
			//并且，将该词记入记号表,标为unrecognized
			while (!isspace(ch = getch(&fin,&count[14],&count[15])) && ch != EOF) {
				buffer += ch;
			};
			table.insertTable(Record(UNRECOGNIZED, buffer));
			if (ch == '\n')
				errTable.insertTable(Record(UNRECOGNIZED, buffer, count[15]));
			else
				errTable.insertTable(Record(UNRECOGNIZED, buffer,count[15]+1));
			if (ch != EOF)ch = getch(&fin,&count[14],&count[15]);
			state = END;
			break;
		}

		}
	} while (ch != EOF);
	count[15]++;//20个换行符说明一共有21行
	ofstream output;
	output.open("output.csv", ios::out | ios::trunc);
	//所有词都分析完毕后，打印整个记号表
	table.printTable(&output,count);
	output << endl <<"total characters,"<<count[14]<<endl<<"total lines,"<<count[15] << endl
		<<"include,"<<count[0] << endl << "id," << count[1] << endl << "keyword," << count[2] << endl << "int," << count[3] << endl << "double," << count[4] << endl
		<< "char," << count[5] << endl << "string," << count[6] << endl << "assign_op," << count[7] << endl << "relation_op," << count[8] << endl << "arith_op,"<< count[9] << endl
		<< "logical_op," << count[10] << endl << "comment," << count[11] << endl << "punctuation," << count[12] << endl << "unrecognized," << count[13] << endl<<endl;
	errTable.printError(&output);
	output.close();
	fin.close();
	return 0;
}
