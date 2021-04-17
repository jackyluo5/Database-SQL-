#include <iostream>
#include "../../!includes/STokenizer/stokenizer.h"
#include "../../!includes/Token/token.h"
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <iomanip>

void test_get_token();

using namespace std;

int main()
{    
//    STokenizer temp;

//    temp.print_table();

    char s[] = "oracion is origin in spanish >= 3.14";
    cout<<"string: "<<s<<endl;

    STokenizer stk(s);
    Token t;
    //The all too familiar golden while loop:
    stk>>t;
    while(stk.more()){
        //process token here...
        cout<<setw(10)<<t.type_string()<<setw(10)<<"|"<<t<<"|"<<endl;

        t = Token();
        stk>>t;
    }


    cout<<"================END OF MAIN==============="<<endl;

    return 0;
}

void test_get_token(){
    char test[50] = "aabaaa";
    string token;

    //set amount of rows and cols
    int rows = 10;
    int cols = 127;

    //declare the table
    int table[rows][cols];

    //initialize table to -1
    for(int i=0; i<cols; i++){
        for(int j=0; j<rows; j++){
            table[i][j] = 1;
        }
    }
    cout<<"init table "<<endl;


    ////print
    //    for(int i=0; i<rows; i++){
    //        for(int j=0; j<cols; j++){
    //            cout<<table[i][j]<<" ";
    //        }
    //        cout<<endl;
    //    }

    //set states
    table[0][97] = 1;
    table[1][97] = 1;
    table[2][97] = 3;
    table[3][97] = 3;

    table[0][98] = 2;
    table[1][98] = 2;
    cout<<"after setting states"<<endl;


    int state = 0;
    int position = 0;

    for(int l = position; l<strlen(test); l++){
        //        cout<<" l = "<<l<<endl;
        //        cout<<"test[l]: "<<test[l]<<endl;
        //        cout<<"===========beginning state: "<<state<<endl;
        //        cout<<"table at [i][j] : "<<table[state][test[l]]<<endl;
        state = table[state][test[l]];

        if(state != -1){
            //            state = table[state][test[l]];
            token += test[l];
            position = l;

            //keep track of position
            //add another condition to check for success state
        }else{
            cout<<"invalid "<<endl;
            break;
        }
        position++;
    }


    cout<<endl<<endl<<endl;
    cout<<"position: "<<position<<endl;
    cout<<"state: "<<state<<endl;
    cout<<"Token: "<<token<<endl;

}
