#include "token.h"

Token::Token()
{
    _token = "";
    _type = NONE;
}
Token::Token(string str, int type){
    _token = str;
    _type = type;
}
int Token::type(){
    return _type;
}
void Token::set_type(int type){
    _type = type;
}
void Token::set_string(string str){
    _token = str;
}
string Token::type_string(){
    //return the types of each character
    switch (_type) {
    case ALPHA:
        return "ALPHA";
    case NUMBER:
        return "NUMBER";
    case PUNCT:
        return "PUNCT";
    case SPACE:
        return "SPACE";
    default:
        return "UNKNOWN";
    }
}
string Token::token_str(){
    return _token;
}
