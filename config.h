#pragma once
#include <string>
#include <iostream>

using namespace std;

//所有的状态
enum State {
	BEGIN,

	ID_KEYWORD_0,
	SYMBOL_0, // +
	SYMBOL_1, // -
	SIGNED_DIGIT_0,
	SYMBOL_2, // *
	SYMBOL_3, // %
	SYMBOL_4, // /
	SYMBOL_5, // >
	SYMBOL_6, // <
	SYMBOL_7, // &
	SYMBOL_8, // |
	SYMBOL_9, // !
	SYMBOL_10, // =
	SYMBOL_11, // '
	SYMBOL_12, // "
	PUNCTUATION_0,

	END,
	ERROR
};

const int MAX_RECORD_NUMBER = 1000;

//词法类型
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
const int KETWORD_NUMBER = 32;
const string KETWORD_TABLE[KETWORD_NUMBER] = {
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
