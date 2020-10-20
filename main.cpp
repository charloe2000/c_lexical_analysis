#include <iostream>
#include "config.h"
#include "utils.h"

using namespace std;

int main(){
    State state = BEGIN;
    Table table;
    string buffer;
    char ch;

    do{
        switch(state){
            case BEGIN:{
                while(isspace(ch = getchar()));
                if(!isspace(ch))
                    buffer += ch;

                    

                if(isalpha(ch) || ch == '_'){
                    state = ID_0;                   
                }
                else {
                    state = ERROR;
                }
                break;
            }

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

            case END:{
                buffer = "";
                state = BEGIN;
                break;
            }

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

    table.printTable();

    return 0;
}   