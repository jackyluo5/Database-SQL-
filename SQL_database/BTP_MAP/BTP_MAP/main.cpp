#include <string>
#include <iostream>
#include "../../!includes/Map/map.h"
#include "../../!includes/MMap/mmap.h"
#include "../../!includes/Map_BPT/map_bpt.h"

using namespace std;

void test_iterator();
void test_map();
void test_mmap();
void test_map_bpt();

int main()
{
    cout << "Hello World!" << endl;

    test_iterator();
//    test_map();
//    test_mmap();
//    test_map_bpt();

    return 0;

}


void test_iterator(){
//    Map_BPT<string, int> temp;
//    Map_BPT<string, int>::Iterator cursor = temp.begin();

//    temp.insert("jan", 5);
//    temp.insert("feb", 8);
//    temp.insert("april", 1);

//    cout << temp <<endl;

//    cursor = temp.begin();
//    cout << *cursor <<endl;
//    cursor++;
//    cout << *cursor <<endl;
//    cursor++;
//    cout << *cursor <<endl;
//    cursor++;
//    cout << *cursor <<endl;

    MMap<string, int> test;
    MMap<string, int>::Iterator point;

    test.insert("jan", 5);
    test.insert("feb", 8);
    test.insert("april", 1);

    cout<<test<<endl;


//    point = test.begin();
//    cout<<*point<<endl;
//    point++;
//    cout<<*point<<endl;
//    point++;
//    cout<<*point<<endl;
    //hits end of list here
//    point++;
//    cout<<*point<<endl;


    cout<<endl;
    for(point = test.begin(); point!=test.end(); point++){
        cout<< "[" << *point << "]";
    }
    cout<<endl<<"finished iteration"<<endl;
}

void test_map(){

    Map<string, int> temp;

    temp.insert("jan", 5);
    temp.insert("feb", 4);
    temp.insert("march", 3);
    temp.insert("april", 2);
    temp.insert("may", 1);

    cout << temp <<endl;

//    temp.erase("may");
//    temp.erase("jan");

//    cout << temp <<endl;

//    temp["may"] += 13;
//    temp.get("jan");

    Pair<string, int> test("may");
    temp.contains(test);


    //testing += operator
//    Pair<string, int> temp1("jan", 200);
//    Pair<string, int> temp2("jan", 3);
////    Pair<string, int> temp3("feb", 23);

//    cout<<"this is TEMP :   ";
//    cout<<temp1<<endl;

//    cout<<"this is TEMP2 :   ";
//    cout<<temp2<<endl;

//    cout<<"      += operator  : ";
//    temp1 += temp2;
////    temp1 += temp3;
//    cout<< temp1 <<endl;


    cout<< temp<<endl;
}

void test_map_bpt(){
    Map_BPT<string, int> temp;

    temp.insert("jan", 5);
    temp.insert("feb", 8);
    temp.insert("april", 1);

    cout << temp <<endl;

    //[] operator
//    temp["jan"] += 19;
    //get
//    temp.get("jan");
    //find
//    temp.find("jan");

    //contains
    temp.contains(Pair<string, int>("feb"));
//    if(temp.contains(Pair<string, int>("feb", 0))){
//        cout<<"CONTAINS AND FOUND"<<endl;
//    }

    temp.erase("april");

    cout<<temp<<endl;
}

void test_mmap(){
//    BPlusTree<MPair<string, int> > months;

//    months.insert(MPair<string, int>("hello", 1));
//    months.insert(MPair<string, int>("next", 2));
//    months.insert(MPair<string, int>("test", 3));
//    months.insert(MPair<string, int>("program", 4));

//    months.print_tree();

    MMap<string, int> test;

    test["jan"] += 5;
    test["feb"] += 28;
    test["march"] += 4;
    test["dec"] += 3;

//    test.insert("jan", 5);
//    test.insert("feb", 28);
//    test.insert("march", 4);
//    test.insert("dec", 3);

//    MPair<string, int> temp("jan", 13);
//    MPair<string, int> temp2("jan", 2);

//    cout<<"this is TEMP :   ";
//    cout<<temp<<endl;

//    cout<<"this is TEMP2 :   ";
//    cout<<temp2<<endl;

//    cout<<"      += operator  : ";
//    temp += temp2;
//    cout<< temp <<endl;

    //[]
    test["jan"] += 13;
    //find
    test.find("dec");

    cout << test <<endl;

    //get
    test.get("july");

    //contains
    test.contains("jan");

    //erase
    test.erase("dec");
    test.erase("jan");


    cout << test <<endl;

    cout<<"here is the SIZE: ";
    cout<<test.size()<<endl;

}
