#include "shunting_yard.h"

shunting_yard::shunting_yard()
{

}
shunting_yard::shunting_yard(vector<string> in){
    _in = in;
}

Vector<Operator> shunting_yard::infixtopostfix(vector<string> infix){
    Stack<Operator> ops;
    Vector<Operator> postfix;

    const bool debug = false;

    cout<<"INFIX SIZE: "<<infix.size()<<endl;
    for(int i=0; i<infix.size(); i++){
//        cout<<"START: "<<infix[i]<<endl;
        Operator hold(infix[i]);
//        cout<<"============================ "<<hold<<endl;

        if(hold.state() != true){
            if(debug) cout<<"not a operator"<<endl;
            //not OPERATOR, push into postfix
            postfix.push_back(hold);
            if(debug) cout<<postfix<<endl;
        }
        else{  //IS AN OPERATOR
            //if operator is empty
            if(ops.empty()){
                if(debug) cout<<"stack is empty"<<endl;
                if(debug) cout<<"hold: "<<hold<<endl;
                ops.push_in(hold);
            }
            else{
                //while stack is not empty, infix prec < stack prec,
                //  pop from stack into the postfix vector
                while(!ops.empty() &&
                      hold.prec() <= ops.tops().prec()){
                    if(debug) cout<<"PREC: "<<hold.prec()<<" "<<hold.op()<<endl;
                    if(debug) cout<<"STACK PREC: "<<ops.tops().prec()<<" "<<ops.tops().op()<<endl;

                    postfix.push_back(ops.pop_back());
                }
                ops.push_in(hold);
            }
        }
    }
    if(debug)cout<<"reached end: "<<endl;
    if(debug) ops.print_stack();
    while(!ops.empty()){
        postfix.push_back(ops.pop_back());
    }


    if(debug) cout<<"here is the final postfix: ";
    return postfix;


}
