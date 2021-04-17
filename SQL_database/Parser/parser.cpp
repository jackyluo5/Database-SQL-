#include "parser.h"
#include <string.h>

typedef MMap<string, string> mmap_ss;
typedef Map_BPT<string, int> map_keywords;

Parser::Parser()
{
    //check table
    Init_table(_table);
    make_table();
}

Parser::Parser(char input[]){
    const bool debug = true;

    //initialize adjacency table
    Init_table(_table);
    //build keyword list
    make_table();

    //fill vector
    fill_vector(input);
    if (debug) cout << "input: " << _input <<endl;
    //fill keywords
    fill_keywords();
    if (debug) cout << "keyword: " << endl << _keywords <<endl;

    if (!build_ParseTree()){
        throw (INVALID_COMMAND);
    }

    if (debug) cout << "parse tree " << endl << _ptree << endl;
}

mmap_ss Parser::get_ParseTree(){
    return _ptree;
}

//return map of keywords
map_keywords Parser::get_keywords(){
    return _keywords;
}

//sets string
void Parser::fill_vector(char input[]){
    const bool debug = false;
    if(debug) cout<< "filling vector"<<endl;

    STokenizer stk(input);
    Token token;

    stk>>token;

    while(stk.more()){
        if (token.type() != UNKNOWN){
            if (debug) cout << "fill_vector() : pushing token [" << token << "] "
                            << endl;

            _input.push_back(token);
        }
        token = Token();
        stk >> token;
    }
}

void Parser::fill_keywords(){
    const bool debug = false;
    if (debug) cout << "filling keywords"<<endl;

    for(int i=0; i<_input.size(); i++){
        if (debug) cout << "fill_keywords() : inserting " << _input[i] << endl;
        insert_tokenType(_input[i]);
    }

    if (debug) cout <<_keywords <<endl;
}

void Parser::insert_tokenType(Token t){
    const bool debug = false;
    if (debug) cout << "inserting token TYPE"<<endl;

    //create table TABLE_NAME with fields FIELD_NAMES
    //insert int TABLE_NAME values VALUES
    //select * from TABLE_NAME

    string token_str = t.token_str();

    if(token_str == "select")           //SELECT COMMAND
        _keywords[token_str] = SELECT;
    else if(token_str == "*")
        _keywords[token_str] = ASTERISK;
    else if(token_str == "from")
        _keywords[token_str] = FROM;
    else if(token_str == "where")
        _keywords[token_str] = WHERE;
    else if (token_str == "insert")     // INSERT COMMAND
        _keywords[token_str] = INSERT;
    else if (token_str == "into")
        _keywords[token_str] = INTO;
    else if (token_str == "values")
        _keywords[token_str] = VALUES;
    else if(token_str == "create" || token_str == "make")
        _keywords[token_str] = CREATE;  // CREATE COMMAND
    else if (token_str == "table")
        _keywords[token_str] = TABLE;
    else if(token_str == "fields")
        _keywords[token_str] = FIELDS;
    else if (token_str == "batch")
        _keywords[token_str] = BATCH;
    else if (isrelationaloperator(token_str))   //COMPARING OPERATORS
        _keywords[token_str] = RELATIONAL_OPERATOR;
    else if (token_str == "and")
        _keywords[token_str] = AND;
    else if (token_str == "or")
        _keywords[token_str] = OR;
    else if (token_str == ",")
        _keywords[token_str] = COMMA;
    else if (token_str == " ")
        _keywords[token_str] = BLANK;
    else if (token_str == "\"")
        _keywords[token_str] = QUOTE;
    else {
        _keywords[token_str] = SYMBOL;
    }

    if (debug) cout << "keyword inserted = " << _keywords[token_str] <<endl;
}
int Parser::get_column(Token t){
    const bool debug = false;

    string token_str = t.token_str();
    if (_keywords.contains(Pair<string, int>(token_str, t.type()))){
        if (debug) cout << "get_columns() : Returning " << _keywords[token_str]
                           << " from " << token_str << endl;
        return _keywords[token_str];
    }
    else{
        if (debug) cout << "get_columns() : Returning SYMBOL for " << token_str
                        << endl;
        return SYMBOL;
    }
}

//build parse tree from string
bool Parser::build_ParseTree(){
    const bool debug = false;
    if (debug) cout << "build_parseTree" << endl;

    int state = 0, last_state = 0, last_key = 0, column = 0;
    string quoted_token = "";

    //Loop vector
    for (int i = 0; i < _input.size(); i++){
        if (debug) cout << "vector at " << i << " :: " << _input[i] << endl;

        // get next token at each iteration
        Token token = _input[i];

        // Set strings and value for token
        string token_str = token.token_str();   //gets token as string
        int token_type = token.type();

        //Check if token_str is in the keyword map, if not it's a symbol,
        //otherwise,   return keywords[token_str]
        column = get_column(Token(token_str, token.type()));

        // Record previous state
        last_state = state;
        // Determine the token's state
        state = _table[state][column];

        // If token's state was a FAIL, end
        if (state == FAIL){
            if (debug) cout << token_str << " failed. " << endl;
            if (debug) assert(true && "Fail State Reached. CHECK COMMAND.\n");


            //accomodates for spaces in string
            if (token_str == " "){
                if(debug) cout << "re-iterate state because of SPACE" << endl << endl;
                state = last_state;
            }
            else{
                if (debug) cout << "Error: Invalid Command" << endl << endl;

                throw (INVALID_COMMAND);
                //return false;
            }
        }

        if(!insert_key_into(last_key, column, token_str, quoted_token))
            if (debug) cout << "|| " << token_str << " failed to insert.\n";
    }

    if (debug) cout << state <<endl << " final state = " << _table[state][0] << endl;
    if (_table[state][0] == 1){
        if (debug) cout << endl << "build_parseTree() : true " << endl;
        return true;
    }
    else {
        if (debug) cout << endl << "build_parseTree() : false" << endl;
        return false;
    }
}

//insert key into parse tree
bool Parser::insert_key_into(int &last_key, int column, string token_str,
                                                string& quoted_token){
    const bool debug = false;

    if (debug) cout << "Determining " << token_str << " with v: " << column
                    << endl;

    switch (column){
    case COMMA :
    case BLANK :
        if (last_key == QUOTE)
            quoted_token += token_str;
        break;
    case SELECT:
    case INSERT:
    case CREATE:
    case MAKE :
        _ptree["Command"] += token_str;
        last_key = column;
        break;
    case BATCH :
    case FROM :
    case FIELDS :
    case TABLE :
    case INTO:
    case VALUES:
    case WHERE:
        last_key = column;
        break;
    case ASTERISK :
        _ptree["Fields"] += token_str;
        break;
    case RELATIONAL_OPERATOR :
    case AND :
    case OR :
        _ptree["Expression"] += token_str;
        last_key = column;
        break;
    case QUOTE :
        if (last_key == QUOTE && _ptree["Command"][0] == "insert"){
            //if quote add concatenation
            _ptree["Values"] += quoted_token;
            quoted_token.clear();               //clear quoted token
            last_key = VALUES;                  //reset
        }
        else if (last_key == QUOTE && _ptree["Command"][0] == "select"){
            _ptree["Expression"] += quoted_token;

            quoted_token.clear();               //clear quoted token
            last_key = VALUES;                  //reset
        }
        else
            last_key = column;
        break;
    case SYMBOL:
        switch (last_key){
        case SELECT:
        case FIELDS:
            _ptree["Fields"] += token_str;
            break;
        case WHERE:
        case RELATIONAL_OPERATOR :
        case AND :
        case OR:
            _ptree["Expression"] += token_str;
            break;
        case TABLE:
        case FROM:
        case INTO:
            _ptree["Table Name"] += token_str;
            break;
        case VALUES:
            _ptree["Values"] += token_str;
            break;
        case BATCH:
            _ptree["Batch"] += token_str;
            break;
        case QUOTE:
            quoted_token += token_str;
            break;
        default :
            if (debug) cout << token_str << " symbol was not recognized" << endl;
        }
        break;
    default :
        if (debug) cout << token_str << " was not inserted" << endl;
        return false;
    }
    return true;
}

bool Parser::isrelationaloperator(string s){
    switch (s[0]){
        case '<':
        case '>':
        case '=':
            return true;
        default :
            return false;
    }
}

bool Parser::isvalue(string s){
    if((s[0] == '\"') && (s[s.back()] == '\"')){
        return true;
    }
    return false;
}



//MAKE TABLE FUNCTIONS
void Parser::Mark_success(int table[][PARSER_COLUMNS], int state){
    table[state][0] = 1;
}
void Parser::Mark_fail(int table[][PARSER_COLUMNS], int state){
    table[state][0] = 0;
}
void Parser::Mark_cell(int table[][PARSER_COLUMNS], int row, int col, int state){
    table[row][col] = state;
}
void Parser::Init_table(int table[][PARSER_COLUMNS]){
    for (unsigned int i=0; i<PARSER_ROWS; i++){
            for (unsigned int j=0; j<PARSER_COLUMNS; j++){
                table[i][j] = -1;
            }
    }
}
void Parser::make_table(){
    //MARK SUCCESS / FAIL STATES

    Mark_fail(_table, ROW0);    //row 0 will fail if no token is inputted

    //ROW 0
    Mark_cell(_table, ROW0, CREATE, STATE1);
    Mark_cell(_table, ROW0, MAKE, STATE1);
    Mark_cell(_table, ROW0, SELECT, STATE11);
    Mark_cell(_table, ROW0, INSERT, STATE25);
    Mark_cell(_table, ROW0, BATCH, STATE30);

    //                            COMMAND MACHINE                               //
    /* NONSUCCESS STATES until a completed command is INPUTTED */
    Mark_fail(_table, ROW1);
    Mark_fail(_table, ROW2);
    Mark_fail(_table, ROW3);
    Mark_fail(_table, ROW4);
    Mark_success(_table, ROW5);
    Mark_fail(_table,ROW6);

    // ---------------------------------------------------------------------//

    //ROW 1
    Mark_cell(_table, ROW1, TABLE, STATE2);
    //ROW 2
    Mark_cell(_table, ROW2, SYMBOL, STATE3);
    //ROW 3
    Mark_cell(_table, ROW3, FIELDS, STATE4);
    //ROW 4
    Mark_cell(_table, ROW4, SYMBOL, STATE5);

    //ROW 5
    Mark_cell(_table, ROW5, SYMBOL, STATE5);
    Mark_cell(_table, ROW5, COMMA, STATE6);

    //ROW 6
    Mark_cell(_table, ROW6, SYMBOL, STATE5);  //go back STATE5, if symbol

    //ROW 7 - 10

    // ---------------------- SELECT COMMAND MACHINE ------------------//
        /* NONSUCCESS STATES until a completed command is INPUTTED */
    Mark_fail(_table, ROW11);               //select *
    Mark_fail(_table, ROW12);               //select * from
    Mark_fail(_table, ROW13);               //select * from <TABLENAME>
    Mark_fail(_table, ROW14);
    Mark_fail(_table, ROW15);
    Mark_success(_table, ROW16);
    Mark_fail(_table, ROW17);
    Mark_fail(_table, ROW18);
    Mark_fail(_table, ROW19);
    Mark_success(_table, ROW20);
    Mark_fail(_table, ROW21);
    Mark_fail(_table, ROW22);

    // ---------------------------------------------------------------------//

    //ROW 11
    Mark_cell(_table, ROW11, SYMBOL, STATE12);
    Mark_cell(_table, ROW11, ASTERISK, STATE14);

    //ROW 12
    Mark_cell(_table, ROW12, SYMBOL, STATE12);
    Mark_cell(_table, ROW12, COMMA, STATE13);
    Mark_cell(_table, ROW12, FROM, STATE15);

    //ROW 13, COMMA LOOP
    Mark_cell(_table, ROW13, SYMBOL, STATE12);

    //ROW 14, ASTERICK
    Mark_cell(_table, ROW14, FROM, STATE15);

    //ROW 15,
    Mark_cell(_table, ROW15, SYMBOL, STATE16);

    //ROW 16
    Mark_cell(_table, ROW16, WHERE, STATE17);

    //ROW 17
    Mark_cell(_table, ROW17, SYMBOL, STATE18);

    //ROW 18
    Mark_cell(_table, ROW18, RELATIONAL_OPERATOR, STATE19);

    //ROW 19
    Mark_cell(_table, ROW19, SYMBOL, STATE20);
    Mark_cell(_table, ROW19, QUOTE, STATE21);

    //ROW 20       SUCCESS STATE
    Mark_cell(_table, ROW20, SYMBOL, STATE20);

    //OPERATOR TO RESET TABLE
    Mark_cell(_table, ROW20, AND, STATE17);
    Mark_cell(_table, ROW20, OR, STATE17);

    //ROW 21 QUOTES
    Mark_cell(_table, ROW21, SYMBOL, STATE21);
    Mark_cell(_table, ROW21, COMMA, STATE21);
    Mark_cell(_table, ROW21, BLANK, STATE22);

    //loop back to success state
    Mark_cell(_table, ROW21, QUOTE, STATE20);

    //ROW 22
    Mark_cell(_table, ROW22, SYMBOL, STATE21);
    Mark_cell(_table, ROW22, QUOTE, STATE20);

    //23 -24 gap

    // ---------------------- INSERT COMMAND MACHINE ------------------//
    /* NONSUCCESS STATES until a completed command is INPUTTED */
    Mark_fail(_table, ROW25);
    Mark_fail(_table, ROW26);
    Mark_fail(_table, ROW27);
    Mark_fail(_table, ROW28);
    Mark_success(_table, ROW29);
    Mark_fail(_table, ROW30);
    Mark_fail(_table, ROW31);
    Mark_fail(_table, ROW32);

    // -----------------------------------------------------------------//

    //INSERT COMMANDS
    //ROW 25
    Mark_cell(_table, ROW25, INTO, STATE26);

    //ROW 26
    Mark_cell(_table, ROW26, SYMBOL, STATE27);

    //ROW 27
    Mark_cell(_table, ROW27, VALUES, STATE28);

    //ROW 28
    Mark_cell(_table, ROW28, SYMBOL, STATE29);
    Mark_cell(_table, ROW28, QUOTE, STATE31);

    //ROW 29 SUCCESS STATE
    Mark_cell(_table, ROW29, SYMBOL, STATE29);
    Mark_cell(_table, ROW29, COMMA, STATE30);
    Mark_cell(_table, ROW29, QUOTE, STATE31);

    //ROW 30 COMMA STATE
    Mark_cell(_table, ROW30, SYMBOL, STATE29);
    Mark_cell(_table, ROW30, QUOTE, STATE31);

    //ROW 31 QUOTE STATE
    Mark_cell(_table, ROW31, SYMBOL, STATE31);

    Mark_cell(_table, ROW31, BLANK, STATE32);
    Mark_cell(_table, ROW31, COMMA, STATE31);

    //LOOP BACK TO SUCCESS STATE
    Mark_cell(_table, ROW31, QUOTE, STATE29);

    //ROW 32  BLANK STATE FROM QUOTE
    Mark_cell(_table, ROW31, BLANK, STATE32);

    // LOOP BACKWARD IF SYMBOL
    Mark_cell(_table, ROW32, SYMBOL, STATE31);

    // FINISH OFF AT SUCCESS
    Mark_cell(_table, ROW32, QUOTE, STATE29);

    //33-34 GAP

    // ---------------------- BATCH COMMAND MACHINE ---------------------//
    /* NONSUCCESS STATES until a fileName is given */
    Mark_fail(_table, ROW35);
    Mark_success(_table, ROW36);
    // -----------------------------------------------------------------//

    //ROW 35
    Mark_cell(_table, ROW35, SYMBOL, STATE36);

}

ostream& Parser::print_parser(ostream& out){
    out << _input;
    return out;
}
