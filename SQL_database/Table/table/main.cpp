#include <iostream>
#include "../../!includes/Table/table.h"
#include "../../!includes/Parser/parser.h"
//#include "../../!includes/MMap/mmap.h"
#include "../../!includes/Operator/operator.h"
#include "../../../CS3A/!inludes/Stack/stack_iterator_Copy.h"
#include "../../../CS3A/!inludes/Vector/vector.h"
#include "../../!includes/RPN/rpn.h"

using namespace std;

void test_table();
void test_parser();
void test_operators();
void test_shunt_yard();
void test_stack();
void test_rpn();

int main()
{
    cout << "Hello World!" << endl;

//    test_table();
//    test_parser();

//    test_stack();

//    test_operators();
    test_shunt_yard();

//    test_rpn();



    return 0;
}

void test_table(){
    vectorstr record = {
        {"first", "last", "age", "major"}
    };
    Table table("emp", record);

    //    vectorstr inputs = {
    //        {"joe", "baker", "23", "CS"}
    //    };

    table.insert_into({"joe", "baker", "23", "CS"});
    table.insert_into({"dan", "kidd", "19", "hum"});
    table.insert_into({"mark", "hamill", "44", "actor"});
    table.insert_into({"rick", "daniels", "14", "athlete"});

    table.select_all();

    cout<<endl<<endl;

    cout<<table;

    cout<<endl<<endl;

//    table.print_table();

//    Table te("emp");
//    cout<<te<<endl;

//    t.load_existing("emp");
//    cout<<t<<endl;

    //select all
//    Table y;
//    y = table._select_all({"select", "*", "last"});
//    cout<<y<<endl;

//    //drops table
//    table.drop();
//    cout<<table<<endl;

    //select
    Table t = table.select({"first", "=", "joe"});
    cout << t;
}

void test_parser(){
    Parser p("select * from emp");
    MMap<string,string> ptree = p.get_ParseTree();

    cout<<ptree;
    if(ptree["Command"][0] == "select"){
        cout<<"Command at 0 is select: "<<endl;
        string string_table = ptree["Table Name"][0];
        cout<<string_table<<endl;
//        Table t(string_table);
//        cout<<endl<<endl<<t<<endl;
    }
    cout<<"after if statement: "<<endl;

//    if(ptree["command"][0] == string("select")){
//        string table_name = ptree["table"][0];
//        cout<<"is select"<<endl;
//    }
}

void test_operators(){
    vector<string> temp = {
        {"my", "name", "=", "AND", "jeff"}
    };

    Operator op(temp[3]);

    if(op.state() == true){
        cout<<"TRUE: "<<endl;
    }else{
        cout<<"FALSE: "<<endl;
    }
    cout<<op.op()<<endl;
    cout<<op.prec()<<endl;


}

void test_shunt_yard(){
    Vector<Operator> temp;
    vector<string> ins = {
        {"last", "=", "jones", "OR", "first", "=", "bill", "AND", "major", "=", "cs"}
    };

    shunting_yard shunt(ins);

    temp = shunt.infixtopostfix(ins);

    cout<<temp<<endl;
}

void test_stack(){
//    Stack<int> temp;

    Stack<Operator> temp;

    Operator hold("=");

    temp.push_in(hold);

//    cout<<"stacK "<<temp<<endl;
//    while(!temp.empty()){
//        cout<<"stack size: "<<temp.size()<<endl;
//        cout<<"stack is not empty: "<<endl;
//        cout<<temp.pop_back()<<endl;
//    }

    Operator test(temp.pop_back());

    cout<<endl<<"this is test: "<<test.op()<<endl;
}
void test_rpn(){
    Table test;
    Vector<Operator> temp;
    vector<string> ins = {
        {"last", "=", "jones"}
//        {"last", "=", "jones", "OR", "first", "=", "bill", "AND", "major", "=", "cs"}
    };

    shunting_yard shunt(ins);

    temp = shunt.infixtopostfix(ins);

    cout<<temp<<endl;


//    vector<long> recnos;

    test.rpn_evaluate(temp);

//    cout<<recnos;
//    RPN post(recnos);

//    post.evaluate(temp);


}
