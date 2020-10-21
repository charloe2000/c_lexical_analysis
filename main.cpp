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
	//当前字符
	char ch;
	//当前词
	string buffer;

	ifstream fin;
	fin.open("code.txt");
	while (isspace(ch = fin.get()));
	do {
		switch (state) {
			//开始状态
		case BEGIN: {
			//进入开始状态时ch保证是不为空且不为空格的
			//把字符加入到当前词
			buffer += ch;

			
			if (isalpha(ch) || ch == '_') state = ID_KEYWORD_0;	// 标识符或关键字			
			//else if (ch == '+') state = SYMBOL_0;// +
			//else if (ch == '-') state = SYMBOL_1;// -
			//else if (isdigit(ch)) state = SIGNED_DIGIT_0;// 数
			else if (ch == '*') state = SYMBOL_2;// *
			else if (ch == '%') state = SYMBOL_3;// %
			else if (ch == '/') state = SYMBOL_4;// /
			else if (ch == '>') state = SYMBOL_5;// >
			else if (ch == '<') state = SYMBOL_6;// <
			else if (ch == '&') state = SYMBOL_7;// &
			else if (ch == '|') state = SYMBOL_8;// |
			else if (ch == '!') state = SYMBOL_9;// !
			else if (ch == '=') state = SYMBOL_10;// =
			else if (ch == ' \'') state = SYMBOL_11;// '
			else if (ch == '\"') state = SYMBOL_12;// "
			else if (ch == ',') state = PUNCTUATION_0;// 标点
			else if (ch == ';') state = PUNCTUATION_0;// 标点
			else if (ch == '(') state = PUNCTUATION_0;// 标点
			else if (ch == ')') state = PUNCTUATION_0;// 标点
			else if (ch == '{') state = PUNCTUATION_0;// 标点
			else if (ch == '}') state = PUNCTUATION_0;// 标点
			else state = ERROR;//词法错误
			break;
		}

		//标识符或关键字的第一个状态
		case ID_KEYWORD_0: {
			ch = fin.get();

			if (isalpha(ch) || isdigit(ch) || ch == '_') {
				//state = ID_KEYWORD_0;
				buffer += ch;
			}
			else {
				bool keyword_flag = false;
				for (int i = 0; i < KETWORD_NUMBER; ++i) {
					if (buffer == KETWORD_TABLE[i]) {
						table.insertTable(Record(KEYWORD, buffer));
						state = END;
						keyword_flag = true;
						break;
					}
				}
				if (!keyword_flag) {
					table.insertTable(Record(ID, buffer));
					state = END;
				}
			}
			break;
		}
		// +
		case SYMBOL_0: {
			ch = fin.get();

			if (ch == '+' || ch == '=') {
				buffer += ch;
				table.insertTable(Record(ARITH_OP, buffer));
				ch = fin.get();
				state = END;
			}
			else if (isdigit(ch)) {
				state = SIGNED_DIGIT_0;
			}
			else {
				table.insertTable(Record(ARITH_OP, buffer));
				state = END;
			}
			break;
		}
		// -
		case SYMBOL_1: {
			ch = fin.get();

			if (ch == '-' || ch == '=') {
				buffer += ch;
				table.insertTable(Record(ARITH_OP, buffer));
				ch = fin.get();
				state = END;
			}
			else if (isdigit(ch)) {
				state = SIGNED_DIGIT_0;
			}
			else {
				table.insertTable(Record(ARITH_OP, buffer));
				state = END;
			}
			break;
		}

		//数
		/*case SIGNED_DIGIT_0: {
			ch = fin.get();

			if ( isdigit(ch) ) {
				buffer += ch;
			}
			else if (ch == '.') {

			}
			else {
				table.insertTable(Record(ID, buffer));
				state = END;
			}
			break;
		}*/
		// *
		case SYMBOL_2: {
			ch = fin.get();

			if (ch == '=') {
				buffer += ch;
				table.insertTable(Record(ARITH_OP, buffer));
				ch = fin.get();
				state = END;
			}
			else {
				table.insertTable(Record(ARITH_OP, buffer));
				state = END;
			}
			break;
		}
		// %
		case SYMBOL_3: {
			ch = fin.get();

			if (ch == '=') {
				buffer += ch;
				table.insertTable(Record(ARITH_OP, buffer));
				ch = fin.get();
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
				while (isspace(ch = fin.get()));
			}
			buffer = "";
			state = BEGIN;
			break;
		}

				  //遇到无法解析的词法
		case ERROR: {
			//如果遇到无法识别的词,把该词剩余字符读取完毕
			//并且，将该词记入记号表,标为unrecognized
			while (!isspace(ch = fin.get()) && ch != EOF) {
				buffer += ch;
			};
			if (ch != EOF)ch = fin.get();
			table.insertTable(Record(UNRECOGNIZED, buffer));
			state = END;
			break;
		}

		}
	} while (ch != EOF);

	//所有词都分析完毕后，打印整个记号表
	table.printTable();
	fin.close();
	
	return 0;
} 
