#ifndef STOKENIZER_H
#define STOKENIZER_H

#include "../../!includes/Token/token.h"
#include <iostream>
#include <cstring>

using namespace std;
const int MAX_COLUMNS = 127;
const int MAX_ROWS = 80;
const int MAX_BUFFER = 500;


class STokenizer
{
public:
    STokenizer();
    STokenizer(char str[]);
    bool done();            //true: there are no more tokens
    bool more();            //true: there are more tokens
    //==================================================
    //managing table functions

    //mark this row(state) as success
    void mark_success(int _table[][MAX_COLUMNS], int state);
    //mark this row(state) as fail
    void mark_fail(int _table[][MAX_COLUMNS], int state);

    //mark a SPECIFIC cell with a state in the table
    void mark_cell(int row, int col, int state);
    //set a row with a state

    void mark_cells_in_row(int row, int start, int end, int state);

    //Mark columns represented by the string columns[] for this row
    void mark_cells_in_col(int row, const char columns[], int state);

    //====================================================
    //extract one token (very similar to the way cin >> works)
    friend STokenizer& operator >> (STokenizer& s, Token& t);

    //set a new string as the input string
    void set_string(char str[]);

    //print the table
    void print_table();

private:
    //initialize the table
    void init_table(int _table[][MAX_COLUMNS]);


    //create table for all the tokens we will recognize
    //                      (e.g. doubles, words, etc.)
    void make_table(int _table[][MAX_COLUMNS]);


    //extract the longest string that match
    //     one of the acceptable token types
    bool get_token(int start_state, string &token);
    //int start_state, string &token
    //---------------------------------
    char _buffer[MAX_BUFFER];       //input string
    int _pos;                       //current position in the string
    static int _table[MAX_ROWS][MAX_COLUMNS];
};

#endif // STOKENIZER_H
