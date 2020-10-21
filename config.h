#pragma once
#include <string>
#include <iostream>

using namespace std;

//所有的状态
enum State {
	BEGIN,

	INCLUDE_0, INCLUDE_1, INCLUDE_2, INCLUDE_3, INCLUDE_4, // #include
	ID_KEYWORD_0, // id
	PUNCTUATION_0, //
	ARITH_0, // +
	ARITH_1, // -
	SIGNED_DIGIT_0,
	ARITH_2, // *
	ARITH_3, // %
	ASSIGN_0, // =, ==
	RELATION_0, RELATION_1, RELATION_2, RELATION_3, // >, <, >=, <=, >>, <<
	LOGICAL_0, LOGICAL_1, LOGICAL_2, // &&, ||, !, !=
	SINGLE_QUETO_0, SINGLE_QUETO_1, SINGLE_QUETO_2, // ''
	DOUBLE_QUETO_0, DOUBLE_QUETO_1, DOUBLE_QUETO_2, // ""
	COMMENT_0, COMMENT_1, COMMENT_2, COMMENT_3, // / or /= or // or /* */

	END,
	ERROR
};

const int MAX_RECORD_NUMBER = 1000;

//词法类型
const string INCLUDE = "include";
const string ID = "id";
const string KEYWORD = "keyword";
const string UNSIGNED_INT = "unsigned_int";
const string SIGNED_INT = "signed_int";
const string UNSIGNED_DOUBLE = "unsigned_double";
const string SIGNED_DOUBLE = "signed_double";
const string CHAR = "char";
const string STRING = "string";
const string ASSIGN_OP = "assign_op";
const string RELATION_OP = "relation_op";
const string ARITH_OP = "arith_op";
const string LOGICAL_OP = "logical_op";
const string COMMENT = "comment";
const string PUNCTUATION = "punctuation"; 
const string UNRECOGNIZED = "unrecognized";

//保留字
const int KEYWORD_NUMBER = 32;
const string KEYWORD_TABLE[KEYWORD_NUMBER] = {
	"int",
	"long",
	"short",
	"float",
	"double",
	"char",
	"unsigned",
	"signed",
	"const",
	"void",
	"volatile",
	"enum",
	"struct",
	"union",
	"if",
	"else",
	"goto",
	"switch",
	"case",
	"do",
	"while",
	"for",
	"continue",
	"break",
	"return",
	"default",
	"typedef",
	"auto",
	"register",
	"extern",
	"static",
	"sizeof"
};


//标点符号
const int PUNCTUATION_NUMBER = 8;
const char PUNCTUATION_TABLE[PUNCTUATION_NUMBER] = {
	',',
	';',
	'(',
	')',
	'{',
	'}',
	'[',
	']',
};