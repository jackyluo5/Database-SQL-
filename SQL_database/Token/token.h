#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
#include "../../!includes/state_machine_constants/state_machine_constants.h"
using namespace std;

//enum Type{NUMBER, ALPHA , PUNCT, SPACE , UNKNOWN , NONE = -1};

//enum Table{
//    ROW0 = 0, ROW1 = 1, ROW2 = 2, ROW3 = 3, ROW4 = 4, ROW5 = 5,
//    ROW6 = 6, ROW7 = 7, ROW8 = 8, ROW9 = 9, ROW10 = 10,

//    STATE1 = 1, STATE2 = 2, STATE3 = 3, STATE4 = 4, STATE5 = 5,
//    STATE6 = 6, STATE7 = 7, STATE8 =8, STATE9 = 9, STATE10 = 10,
//};

//enum characters{
//    MAJUSCULE = 128, NBSP = 255
//};

const char DIGITS[] = "1234567890";

class Token
{
public:
    //cotr
    Token();
    Token(string str, int type);

    friend ostream& operator <<(ostream& outs, const Token& t){
        outs << t._token;
        return outs;
    }

    int type();             //return type of token
    void set_type(int type);        //setter for type
    void set_string(string str);    //setter for string
    string type_string();   //return type of token in string
    string token_str();     //return token string itself
private:
    string _token;
    int _type;
};

#endif // TOKEN_H
