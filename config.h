#pragma once
#include <iostream>
using namespace std;

//所有的状态
enum State{
    BEGIN,
    ID_0,
    END,
    ERROR
};

const int MAX_RECORD_NUMBER = 1000;

//词法类型
const string ID = "id";
const string KEYWORD = "keyword";
const string UNRECOGNIZED = "unrecognized";
