#include <iostream>
#include "config.h"
#include "utils.h"

using namespace std;

int main(){
    //开始状态
    State state = BEGIN;
    //记号表
    Table table;
    //当前字符
    char ch;
    //当前词
    string buffer;
    
    do{
        switch(state){
            //开始状态
            case BEGIN:{
                //清除空格字符
                while(isspace(ch = getchar()));
                //把字符加入到当前词
                buffer += ch;

                if(isalpha(ch) || ch == '_'){
                    state = ID_0;                   
                }
                else {
                    state = ERROR;
                }
                break;
            }

            //标识符的第一个状态
            case ID_0:{
                ch = getchar();

                if(isalpha(ch) || isdigit(ch) || ch == '_'){
                    state = ID_0;
                    buffer += ch;
                } else{
                    table.insertTable(Record(ID, buffer));
                    state = END;
                }
                break;
            }

            //读完一个词后，进入END状态
            case END:{
                buffer = "";
                state = BEGIN;
                break;
            }

            //遇到无法解析的词法
            case ERROR:{
                //如果遇到无法识别的词,把该词剩余字符读取完毕
                //并且，将该词记入记号表,标为unrecognized
                while(!isspace(ch = getchar())){
                    buffer += ch;                 
                };
                table.insertTable(Record(UNRECOGNIZED, buffer));
                state = END;
                break;
            }

        }
    }while(ch != '#');

    //所有词都分析完毕后，打印整个记号表
    table.printTable();

    return 0;
}   