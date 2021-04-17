#include "stokenizer.h"

int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];
STokenizer::STokenizer()
{
    _buffer[0] = '\0';
    _pos = 0;
    //initializes table
    init_table(_table);
    //call make table
    make_table(_table);

}
STokenizer::STokenizer(char str[]){
    set_string(str);
    init_table(_table);
    make_table(_table);
}
bool STokenizer::done(){
    //true: there are NO MORE tokens
//    return !more();
    return _pos>strlen(_buffer);
}
bool STokenizer::more(){
    //true: there are MORE tokens
    return !done();
//    return _pos<=strlen(_buffer);
}

//mark this row(state) as success = 1
void STokenizer::mark_success(int _table[][MAX_COLUMNS], int state){
    _table[state][0] = 1;
}
//mark this row(state) as fail = 0
void STokenizer::mark_fail(int _table[][MAX_COLUMNS], int state){
    _table[state][0] = 0;
}


//mark a SPECIFIC cell with a state in the table
void STokenizer::mark_cell(int row, int col, int state){
    _table[row][col] = state;
}
//set a row with a state
//ex: (0, 'a', 'z', 3) sets row 0, from column a to z with state 3
void STokenizer::mark_cells_in_row(int row, int start, int end, int state){
    for(int i=start; i<=end; i++){
        _table[row][i] = state;
    }
}

void STokenizer::mark_cells_in_col(int row, const char columns[], int state){
    for (unsigned int i = 0; columns[i] != '\0'; i++)
        _table[row][int(columns[i])] = state;
}

//extract one token (very similar to the way cin >> works)
STokenizer& operator >> (STokenizer& s, Token& t){
    string temp = "";
//    s.get_token(t);
    //starting state is 0
    if(s.get_token(0, temp)){
        //set the types when getting token
        if (isdigit(temp[0]))
            t.set_type(0);  //numbers
        else if (isalpha(temp[0]))
            t.set_type(1);  //alphas
        else if (ispunct(temp[0]))
            t.set_type(2); //punct
        else if (isspace(temp[0]))
            t.set_type(3); //space
        else
            t.set_type(4); //unknown
        t.set_string(temp);

    }
    return s;
}

//set a new string as the input string
void STokenizer::set_string(char str[]){
    //copy str into buffer
    strcpy(_buffer, str);
    _pos = 0;
}

void STokenizer::print_table(){
    for (unsigned int i=0; i<MAX_ROWS; i++){
        for (unsigned int j=0; j<MAX_COLUMNS; j++)
        {
            cout << _table[i][j] << " ";
        }
        cout << endl;
    }
}



//=====================================
void STokenizer::init_table(int _table[][MAX_COLUMNS]){
    for(int i =0; i<MAX_ROWS; i++){
        for(int j=0; j<MAX_COLUMNS; j++){
            _table[i][j] = -1;
        }
    }
}

void STokenizer::make_table(int _table[][MAX_COLUMNS]){
    //MARK SUCCESS/FAIL STATES

    //ROW1-3 NUMBERS
    mark_fail(_table, 0);
    mark_success(_table, 1);
    mark_fail(_table, 2);
    mark_success(_table, 3);
    //ROW4 WORDS
    mark_success(_table, 4);
    mark_fail(_table, 5);
    mark_success(_table, 6);
    //ROW 7 PUNCTUATION
    mark_success(_table, 7);
    //ROW8 SYMBOLS
    mark_success(_table, 8);

    //0 STARTING STATE
    mark_cells_in_row(0, 'A', 'Z', 4);  //UPPER ALPHA
    mark_cells_in_row(0, 'a', 'z', 4);  //LOWER ALPHA
    mark_cells_in_row(0, '.','.', 2);   //DECIMAL
    mark_cells_in_row(0, '0', '9', 1);  //NUMBERS, DOUBLES
    mark_cells_in_row(0, ' ', '/', 7);  //PUNCT
    mark_cells_in_row(0, ':', '@', 7);  // : -> @
    mark_cells_in_row(0, '[', '\'', 7); // [ -> \'
    mark_cells_in_row(0, '{', '~', 7);  // { -> ~
    mark_cells_in_row(0, 128, 254, 8);// SYMBOLS


    //==============================================
    //NUMBER
    //SUCCESS IF NUMBER IS INPUTTED
    mark_cells_in_row(1, '.','.', 2); //3.14 [1]---DECIMAL--->[2]
    mark_cells_in_row(1, '0', '9', 1);  //   [1]---DIGIT--->[1]

    //SUCCESS IF DECIMAL and THOUSAND, DOUBLE, ex: 3.14 and 385,000.14
    mark_cells_in_row(2, '0', '9', 3);     //[2]---DIGIT--->[3]

    //SUCCESS IF NUMBER IS INPUTTED AFTER DECIMAL
    mark_cells_in_row(3, '0', '9', 3);     //[3]---DIGIT--->[3]

    //==============================================
    //ALPHAS
    //SUCCESS IF ALPHA IS INPUTTED
    //lowercase letters:
    mark_cells_in_row(4, 'A', 'Z', 4);//97-122  [4]---ALPHA--->[4]
        //UPPERCASE LETTERS:
    mark_cells_in_row(4, 'A', 'z', 4);//65-90   [4]---ALPHA--->[4]
        //Apostrophe
    mark_cells_in_row(4, '\'', '\'', 5);//      [4]---'\''--->[5]

    //5 NONSUCCESS STATE IF APOSTROPHE OR - IS INPUTTED
    //lowercase letters:
    mark_cells_in_row(5, 'A', 'Z', 6);    //    [6]---ALPHA--->[6]
        //UPPERCASE LETTERS:
    mark_cells_in_row(5, 'A', 'z', 6);    //    [5]---ALPHA--->[6]

    //6 SUCCESS STATE IF ALPHA IS INPUTTED
    //lowercase letters:
    mark_cells_in_row(6, 'A', 'Z', 6);    //    [6]---ALPHA--->[6]
        //UPPERCASE LETTERS:
    mark_cells_in_row(6, 'A', 'z', 6);    //    [6]---ALPHA--->[6]


    //==============================================
    //PUNCT
    mark_cells_in_row(7, ' ', '/', 7);//32-47  [7]---PUNCT--->[7]
    mark_cells_in_row(7, ':', '@', 7);//58-65  [7]---PUNCT--->[7]
    mark_cells_in_row(7, '[', '\'', 7);//91-96 [7]---PUNCT--->[7]
    mark_cells_in_row(7, '{', '~', 7);//123-126[7]---PUNCT--->[7]

    //===============================================
    //UNKNOWN
    mark_cells_in_row(8, 128, 255, 8);// [8]---SYMBOL--->[8]


//    mark_fail(_table, ROW0);       //first state is fail
//    //ROW 1-5 WORDS / ALPHAS
//    mark_success(_table, ROW1);
//    mark_fail(_table, ROW2);   // apostrophe
//    mark_success(_table, ROW3);
//    //ROW 6-10 NUMBERS / DOUBLES
//    mark_success(_table, ROW6);
//    mark_fail(_table, ROW7);   // decimal
//    mark_success(_table, ROW8);
//    //ROW 11-12 PUNCTUATION
//    mark_success(_table, ROW11);

//    //ROW 15 CHARACTERS
////    mark_success(_table, ROW15);

//    //ROW 20 SPACES
//    mark_fail(_table, ROW20); //space


//    //STARTING STATES
//    mark_cells_in_row(ROW0, ' ', ' ', STATE20); //SPACE
//    mark_cells_in_row(ROW0, 'a', 'z', STATE1);  //UPPER ALPHAS
//    mark_cells_in_row(ROW0, 'A', 'Z', STATE1);  //LOWER ALPHAS
//    mark_cells_in_row(ROW0, '0', '9', STATE6);  //NUMS
//    mark_cells_in_row(ROW0, '.', '.', STATE7);  //DECIMAL
//    mark_cells_in_row(ROW0, '!', '/', STATE11);// PUNCTUATION
//    mark_cells_in_row(ROW0, ':', '@', STATE11);// [: -> @]
//    mark_cells_in_row(ROW0, '[', '\'', STATE11);// [ [ -> \' ]
//    mark_cells_in_row(ROW0, '{', '~', STATE11);  //[ { -> ~ ]
////    mark_cells_in_row(ROW0, MAJUSCULE, 254, STATE15); //SPANISH CHARACTERS


//    //==============================================
//    //ALPHAS
//    //SUCCESS IF ALPHA IS INPUTTED
//    mark_cells_in_row(ROW1, 'a','z', STATE1);   //97-122          [1]---ALPHA--->[1]
//    mark_cells_in_row(ROW1, 'A','Z', STATE1);   //65-90           [1]---ALPHA--->[1]
//    mark_cells_in_row(ROW1, '\'', '\'', STATE2);   //apostrophe   [1]---'\''--->[2]

//    //FAIL IF APOSTROPHE , go to next state
//    mark_cells_in_row(ROW2, 'a','z', STATE3);   //                [2]---ALPHA--->[3]
//    mark_cells_in_row(ROW2, 'A','Z', STATE3);   //                [2]---ALPHA--->[3]

//    //SUCCESS IF ALPHA INPUTTED AFTER APOSTROPHE
//    mark_cells_in_row(ROW3 ,'a','z', STATE3);    //               [3]---ALPHA--->[3]
//    mark_cells_in_row(ROW3, 'A', 'Z', STATE3);   //               [3]---ALPHA--->[3]

//    //==============================================
//    //NUMBER
//    //SUCCESS IF NUMBER IS INPUTTED
//    mark_cells_in_row(ROW6, '0', '9', STATE6);  //48-57          [6]---DIGIT--->[6]
//    mark_cells_in_row(ROW6, '.', '.', STATE7);  // . , 3.14      [6]---DECIMAL--->[7]
////    mark_cells_in_row(6, ',', ',', 11); // , ,33,000

//    //SUCCESS IF DECIMAL and THOUSAND, DOUBLE, ex: 3.14 and 385,000.14
//    mark_cells_in_row(ROW7, '0', '9', STATE8);    //             [7]---DIGIT--->[8]
////    mark_cells_in_row(11, '0', '9', 8);

//    //SUCCESS IF NUMBER IS INPUTTED AFTER DECIMAL
//    mark_cells_in_row(ROW8, '0', '9', STATE8);  //               [8]---DIGIT--->[8]

//    //==============================================
//    //PUNCT
//    mark_cells_in_row(ROW11, '!', '/', STATE11);  //32-47      [11]---PUNCT--->[11]
//    mark_cells_in_row(ROW11, ':', '@', STATE11);  //58-65      [11]---PUNCT--->[11]
//    mark_cells_in_row(ROW11, '[', '\'', STATE11); //91-96      [11]---PUNCT--->[11]
//    mark_cells_in_row(ROW11, '{', '~', STATE11);  //123-126    [11]---PUNCT--->[11


//    //===============================================
//    //UNKNOWN
////    mark_cells_in_row(ROW15, MAJUSCULE, NBSP, STATE15); //SPANISH CHARACTERS


//    //===============================================
//    //SPACE
//    mark_cells_in_row(ROW20, ' ', ' ', STATE20);    //32        [20]---SPACE--->[20]

}
bool STokenizer::get_token(int start_state, string &token){
    int success_pos = _pos;
//    int start_state = 0;
//    string token;

    if(_buffer[0] != '\0'){
        //iterate through cstring, start at position
        for(unsigned int i=_pos; i < strlen(_buffer); i++){
            //get the first state, unsigned int and char is for special characters from buffer
            start_state = _table[start_state][(unsigned int)(unsigned char)_buffer[i]];

            //check if state is success or fail
            if(start_state != -1){
                //add character to the token
                token += _buffer[i];
                //update token
                success_pos = i;

                //sets token and type
//                Token temp(token, start_state);
//                t = temp;
            }else{
                //exit and fail if not correct state
                break;
            }
        }
        //set the final position to character following the final character
        // cut-off of cstring
        _pos = ++success_pos;
        return true;
    }
    else{
        //if it is NULL, point to the one over
        _pos++;
//        cout<<"get_token false: "<<endl;
        return false;
    }
}
