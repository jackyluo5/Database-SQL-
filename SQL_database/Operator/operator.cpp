#include "operator.h"

Operator::Operator()
{

}
Operator::Operator(string op)
{
    _op = op;
    _valid = false;

    if(_op == "="){
        _valid = true;
        _precedence = 3;
    }
    else if(_op == "<="){
        _valid = true;
        _precedence = 3;
    }
    else if(_op == ">="){
        _valid = true;
        _precedence = 3;
    }
    else if(_op == "<"){
        _valid = true;
        _precedence = 3;
    }
    else if(_op == ">"){
        _valid = true;
        _precedence = 3;
    }
    else if(_op == "AND"){
        _valid = true;
        _precedence = 2;
    }
    else if(_op == "OR"){
        _valid = true;
        _precedence = 1;
    }
    else{
        _valid = false;
        _precedence = 20;
    }
}

int Operator::prec(){
    // == , <=  , >= , > , <
    if(_op == "=" || _op == "<=" ||
            _op == ">=" || _op == ">" || _op == "<"){
        _precedence = 3;
    }
    //AND
    if(_op == "AND"){
        _precedence = 2;
    }
    //OR
    if(_op == "OR"){
        _precedence = 1;
    }
    return _precedence;
}

string Operator::op(){
    return _op;
}
int Operator::get_prec(){
    return _precedence;
}
bool Operator::state(){
    return _valid;
}
int Operator::type(){
    return OPERATOR;
}
//void Operator::print(ostream& outs){
//    outs<<_op;
//}

