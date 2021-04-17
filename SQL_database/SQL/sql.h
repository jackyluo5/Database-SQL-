#ifndef SQL_H
#define SQL_H
#include <iostream>
#include <string>
#include <cassert>
#include <iomanip>
#include <fstream>
#include "../../!includes/Parser/parser.h"
#include "../../!includes/Table/table.h"

#include "../../!includes/MMap/mmap.h"
#include "../../!includes/Map_BPT/map_bpt.h"
#include "../../!includes/MPair/mpair.h"
#include "../../!includes/Pair/pair.h"

using namespace std;
enum possibe_input { COMMAND, NONCOMMAND, DEBUG };
enum command_list { SQL_CREATE, SQL_MAKE, SQL_INSERT, SQL_SELECT, SQL_EXIT };


class SQL
{
    //put data into this file to be read
    const string FILE_TABLERECORD = "table_record.txt";

    /* type definitions */
    typedef MMap<string, string> MMStringString;
    typedef Map_BPT<string, int> KeywordMap;
    typedef Map_BPT<char, int> PossibilitiesMap;
    typedef Map_BPT<int, string> ExceptionMap;
    typedef Map_BPT<string, Table> TableMap;

public:
    SQL();
    SQL(const char fileName[]);

    //run
    void run(); //calls run_input on loop

private:

    //===========================================================

    //Current Data
    string _command;
    MMStringString _parsed_command;
    int _command_count;

    //Data Stored
    TableMap _mapped_tables;

    //Maps
    KeywordMap _mapped_commands;
    PossibilitiesMap _mapped_possibilities;
    ExceptionMap _mapped_exceptions;

    //Recorder
//    ofstream _recorder;
//    bool _recorder_on;

    bool batch_mode, prompts = true;

    //===========================================================
    void run_batch(const char fileName[]);      //Run in batch

    bool run_input(char command[], istream &in = cin);

    bool execute(ostream& outs = cout);
    void execute_batch();

    Table process(int command, string tableName);


    //parse incoming command
    bool parse(char input[], MMStringString &command_tree);

    //get command from ifstream
    bool get_input(char input[], istream &in = cin) throw (SQL_exceptions);

    //check command if exceptional
    int validate_input(string s);

    void drop_table(string table_name);

    //Construct maps
    void map_commands();
    void map_possibilities();
    void map_exceptions();
    void map_tables();

    //Errors
    string get_errorMsg(const char command[], SQL_exceptions e);//===


    //Parse Tree - accessors
    int get_command();
    vectorstr get_fields();
    vectorstr get_values();
    vectorstr get_where();
    bool is_batch();
    string get_table();
    bool is_select_all();
    bool is_select_where();
    int get_command_count();

    //Batch - ing
    string build_batch_file_name();
    bool verify_batch_file(string str);

    //Printing
    void print_description();
    void print_results(string command, Table table, ostream &outs = cout);

};

#endif // SQL_H



//void record_table(Table t);
//bool should_drop();
//bool should_record();
//void drop_table(string tableName);

////To get filename
//string append_select_files(vectorstr fields);
