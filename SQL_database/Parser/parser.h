#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <cstring>
#include "../../!includes/STokenizer/stokenizer.h"
#include "../../!includes/Token/token.h"

#include "../../!includes/MMap/mmap.h"
#include "../../!includes/Map_BPT/map_bpt.h"
#include "../../!includes/MPair/mpair.h"
#include "../../!includes/Pair/pair.h"
#include "../../!includes/SQL_constants/sql_exceptions.h"
#include "../../!includes/table_constants/table_constants.h"


using namespace std;

enum ParserTable { PARSER_ROWS = 40, PARSER_COLUMNS = 40 };



enum Keys{
    /* COMMANDS */
        CREATE, MAKE,       //1..2
        INSERT,             //3
        SELECT,             //4
    /* CREATE COMMANDS */
        TABLE,              //5
        FIELDS,             //6
    /* INSERT COMMANDS */
        INTO, VALUES,       //7..8
    /* SELECT COMMANDS */   //9..10..11
        ASTERISK, FROM, WHERE,
    /* OPERATORS */         //12
        RELATIONAL_OPERATOR,
    /* LOGICAL_OPERATORS */
        AND, OR,            //13..14
    /* NON COMMANDS */
        QUOTE, COMMA, BLANK, SYMBOL, BATCH
                            //15..16..17..18
};


class Parser
{
    typedef MMap<string, string> mmap_ss;
    typedef Map_BPT<string, int> map_keywords;
    typedef Map_BPT<int, string> map_states;

public:
    Parser();
    Parser(char input[]);

    //return multi map of input
    mmap_ss get_ParseTree();

    //return map of keywords
    map_keywords get_keywords();

    friend ostream& operator <<(ostream& outs, Parser& print_me){
        return print_me.print_parser(outs);
    }

    //make table functions
    void Mark_success(int table[][PARSER_COLUMNS], int state);
    void Mark_fail(int table[][PARSER_COLUMNS], int state);
    void Mark_cell(int table[][PARSER_COLUMNS], int row, int col, int state);


private:
    vector<Token> _input;   //users input
    map_keywords _keywords; //map for looking up tokens
    mmap_ss _ptree;     //Multi map of parsed commands

    //adjacency matrix
    int _table[PARSER_ROWS][PARSER_COLUMNS];

    //map of states to concatenate
    map_states _concat_states;

    //fill the input vector
    void fill_vector(char input[]);

    //maps keywords
    void fill_keywords();

    //Insert token's TYPE into keywords map
    void insert_tokenType(Token t);

    //gets a tokens column value in state machine
    int get_column(Token t);

    //build parse tree from string
    bool build_ParseTree();

    //insert key into parse tree
    bool insert_key_into(int &last_key, int column, string token_str,
                         string& quoted_token);

    //check strings for comparing
    bool isrelationaloperator(string s);
    bool isvalue(string s);

    //initialize the table
    void Init_table(int table[][PARSER_COLUMNS]);
    //build the table
    void make_table();


    ostream& print_parser(ostream& out = cout);

};

#endif // PARSER_H
