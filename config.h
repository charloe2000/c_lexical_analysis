#pragma once
#include <iostream>
using namespace std;

enum State{
    BEGIN,
    ID_0,
    END,
    ERROR
};

const int MAX_RECORD_NUMBER = 1000;

const string ID = "id";
const string KEYWORD = "keyword";
const string UNRECOGNIZED = "unrecognized";
