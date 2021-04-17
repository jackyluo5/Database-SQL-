#include "../../!includes/state_machine_functions/state_functions.h"
#include <iostream>
using namespace std;


//Fill all cells of the array with -1
void init_table(int _table[][MAX_COLUMNS])
{
    for (unsigned int i=0; i<MAX_ROWS; i++)
        for (unsigned int j=0; j<MAX_COLUMNS; j++)
            _table[i][j] = -1;
}

//Mark this state (row) with a 1 (success)
void mark_success(int _table[][MAX_COLUMNS], int state)
{
    _table[state][0] = 1;
}

//Mark this state (row) with a 0 (fail)
void mark_fail(int _table[][MAX_COLUMNS], int state)
{
    _table[state][0] = 0;
}

//true if state is a success state
bool is_success(int _table[][MAX_COLUMNS], int state)
{
    //returns Row 0 of row (state); 1 or 0: T/f
    return (_table[state][0]);
}

//Mark a range of cells starting at 'from' ending at 'to'
//mark_cells(1, _table, 1, 3, 1)
//marking _table array: row 1 columns 1-3 with state 1
void mark_cells_in_row(int row, int _table[][MAX_COLUMNS], int from, int to, int state)
{
    for (int i=from; i<=to; i++)
        _table[row][i] = state;
}
//set a row with a state
//ex: (0, 'a', 'z', 3) sets row 0, from column a to z with state 3
//void mark_cells_in_row(int row,int start, int end, int state){
//    for(int i=start; i<=end; i++){
//        _table[row][i] = state;
//    }
//}

////Mark columns represented by the string columns[] for this row
//void mark_cells(int row, int _table[][MAX_COLUMNS], const char columns[], int state)
//{
//    //passing an array of chars; marks all columns of those chars
//    for (int i=0; columns[i] != '\0'; i++)
//        _table[row][int(columns[i])] = state;   //casting columns[i] (char) into ascii int
//}

//Mark a specific cell
void mark_cell(int row, int _table[][MAX_COLUMNS], int column, int state)
{
    _table[row][column] = state;
}

//Print items from a relatively small 2D array
void print_table(int _table[][MAX_COLUMNS])
{
    for (unsigned int i=0; i<MAX_ROWS; i++)
    {
        for (unsigned int j=0; j<MAX_COLUMNS; j++)
        {
            cout << _table[i][j] << " ";
        }
        cout << endl;
    }
}

//show string s and mark this position on the string:
//hello world   pos: 7
//       ^
void show_string(int _table[][MAX_COLUMNS], int _pos)
{
    for (unsigned int i = 0; i < MAX_ROWS; i++)
        {
            for (unsigned int j = 0; j < MAX_COLUMNS; j++)
                cout << _table[i][j];
            cout << endl;
        }
}
