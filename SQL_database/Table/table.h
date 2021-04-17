#ifndef TABLE_H
#define TABLE_H
#include "../../!includes/Records/record.h"
//#include "../../!includes/table_constants/table_constants.h"
#include "../../!includes/Map_BPT/map_bpt.h"
#include "../../!includes/MMap/mmap.h"
#include "../../!includes/MPair/mpair.h"
//#include "../../!includes/Map/map.h"
#include "../../!includes/Pair/pair.h"
#include "../../../CS3A/!inludes/Stack/stack_iterator_Copy.h"
#include "../../../CS3A/!inludes/Queue/queue_iterator_Copy.h"
#include "../../!includes/shunting_yard/shunting_yard.h"
#include "../../!includes/Operator/operator.h"
#include "../../!includes/SQL_constants/sql_exceptions.h"

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;


class Table
{
public:
    //CTORS
    Table();
    Table(string name);
    Table(string name, vectorstr field_list);
    void load_existing(string tableName);

    //MODIFIERS
    void insert_into(vectorstr field_list);
    void select_all();
    Table _select_all();
    Table _select_all(vectorstr conditions);
    Table select(vectorstr field_list);
    Table select(vector<string> field_list, vector<string> conditions);

    //rpn and shunt_yard to get recno
    vector<long> get_record_no(vector<string> statement);
    vector<long> rpn_evaluate(Vector<Operator> postfix);

    //drops table
    void drop();

    //re indexing
    bool index(fstream& f, int recno, long &pos);
    void reindex();

    //fill new file with field lists
    void fill_current_fields_from_file(ifstream& in);

    //accessors
    string get_table_name();
    vectorstr get_field_name();

    //setters
    void map_fields();
    bool do_fields_match(vector<string> src, vector<string> fields);

    //prints
    void print_maps();

    void print_current_indices(string msg);

    ostream& print_table(ostream& outs = cout);

    //print table
    friend ostream& operator<<(ostream& outs, Table& print_me){
//        outs<<print_me.indices;
//        return outs;
        return print_me.print_table(outs);
    }


private:
    string _file_name;
    string _name;
    vectorstr _field_list;  //first, last, age, etc.

    Map_BPT<string, int> _map;
    Map_BPT<int, string> _map2;
    vector<MMap<string, long> > indices; //[0]first, [1]last, etc..

    int _serial_no;
};

#endif // TABLE_H
