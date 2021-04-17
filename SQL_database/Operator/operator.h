#ifndef MYOPERATOR_H
#define MYOPERATOR_H
#include <string>
#include <iostream>

using namespace std;

static const int OPERATOR = 3;

class Operator
{
public:
    //ctors
    Operator();
    Operator(string op);

    int prec();

    //accessor
    string op();
    int get_prec();
    bool state();

    int type();

    friend ostream& operator <<(ostream& outs, const Operator& t){
        outs<<t._op<<" ";
        return outs;
    }
    void print(ostream& outs);

private:
    int _precedence;
    string _op;
    bool _valid;
};

#endif // OPERATOR_H
