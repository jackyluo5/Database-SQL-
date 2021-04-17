#include "sql.h"

SQL::SQL(){
    //Default Construct
    print_description();
    const bool debug = false;
    batch_mode = false;

    //create maps
    map_commands();
    map_possibilities();

    //map tables
    if (file_exists(FILE_TABLERECORD.c_str())){
        if(debug) cout<<"mapping table: "<<endl;
        map_tables();                           //map existing tables
    }
    else {
        if(debug) cout<<"file doesn't exist: "<<endl;
        ofstream create_new_file;
        create_new_file.open(FILE_TABLERECORD);
        create_new_file.close();
    }

    _command_count = 0;

    if (debug) cout << "SQL Constructor Fired >> Mode: Interactive\n";
}

SQL::SQL(const char fileName[]){
    //Constructor with batch file
    const bool debug = false;
    batch_mode = false;

    //create maps
    map_commands();
    map_possibilities();

    //map tables
    if (file_exists(FILE_TABLERECORD.c_str())){
        if(debug) cout<<"mapping table: "<<endl;
        map_tables();                           //map existing tables
    }
    else {
        if(debug) cout<<"file doesn't exist: "<<endl;
        ofstream create_new_file;
        create_new_file.open(FILE_TABLERECORD);
        create_new_file.close();
    }

    _command_count = 0;

    if (debug) cout << "SQL Constructor Fired >> Mode: Batch\n";

    run_batch(fileName);

////    if (drop) drop_table(fileName);

    run();
}
void SQL::run(){
    const int MAX_BUFFER = 100000;
    const bool debug = false, print = false;

    MMStringString command_tree;
    char command[MAX_BUFFER];

    while (true){
        do {

            command_tree = MMStringString();
            command[0] = '\0';

            if (!run_input(command))
                assert(true && "! run_input failed critically !\n");

            if (debug) cout << "Command : " << command << endl;


        } while (!parse(command, command_tree));    //loop until clear to parse

        //saves parsed commands
        _command = command;
        _parsed_command = command_tree;



//        if (is_batch()){
//            execute_batch();
//        }
//        else if (!execute())       //Execute
//            assert(true && "||| Failed Execution");


        if (print) cout << "Parser() : \n" << command_tree << endl;
    }
}


void SQL::run_batch(const char fileName[]){
    const int MAX_BUFFER = 100000;
    const bool debug = false, print = false;
    ifstream in;

    batch_mode = true;

    MMStringString command_tree;
    char command[MAX_BUFFER];

    if (!file_exists(fileName))
        throw(INVALID_BATCH_FILE);

    //opens file fileName
    if(file_exists(fileName)){
        in.open(fileName);
    }

    if (debug) cout << "||| Batch: Opening file f: " << fileName << endl;

    while (true){
        try {
            do {
                command_tree = MMStringString();
                command[0] = '\0';

                if (!run_input(command, in))
                    assert(true && "! DID NOT RUN INPUT !\n");

                if (debug) cout << "Command : " << command << endl;

            } while (!parse(command, command_tree));
        }
        catch (SQL_exceptions e) {
            if (e == STREAM_EOF)
                throw (STREAM_EOF);
        }

        //Saves parsed commands
        _command = command;
        _parsed_command = command_tree;

        //Execute

        if (!execute())
            assert(true);


        if (print) cout << "Parser() : \n" << command_tree << endl;

        _command.clear();
        _parsed_command.clear();

    }
}

bool SQL::run_input(char command[], istream &in){
    const bool debug = false;
    bool process = false;

    while (!process){

        if (!batch_mode) cout << "Command : ";

        command[0] = '\n';           //clear buffer

        try {
            if (get_input(command, in))
                process = true;
            else {
                cout << command << endl;
//                _recorder << command << endl;
            }
        }
        //echo catch
        catch (SQL_exceptions e) {
            if (debug) cout << "Exceptions caught\n";

            cout << get_errorMsg(command, e) << endl;
            if (e == STREAM_EOF)
                throw(STREAM_EOF);
        }

    }

    return true;
}

bool SQL::execute(ostream& outs){

    const bool debug = false;

    bool postProcess = true;


    //Get 1 command
    int command = get_command();
    if (debug) cout << "||| Executing a " << _command << endl;

    //Get Name of table
    string tableName = get_table();
    if (debug) cout << "||| Grabbing Table Name : " << tableName << endl;

    Table table;
    try{

        //Process command for table
//        table = process(command, tableName);
        if (debug) cout << "||| Retrieved table\n";
    }

    //Errors
    catch (SQL_exceptions e){

        if (e == UNABLE_TO_PROCESS){
            cout << _mapped_exceptions[UNABLE_TO_PROCESS];
//            _recorder << _mapped_exceptions[UNABLE_TO_PROCESS];
        }
        if (e == UNABLE_TO_EVAL){
            cout << _mapped_exceptions[UNABLE_TO_EVAL];
//            _recorder << _mapped_exceptions[UNABLE_TO_EVAL];
        }
        if (e == FILE_DNE){
            cout << _mapped_exceptions[FILE_DNE];
//            _recorder << _mapped_exceptions[FILE_DNE];
        }
        if (e == FIELDS_MISMATCH){
            cout << _mapped_exceptions[FIELDS_MISMATCH];
//            _recorder << _mapped_exceptions[FIELDS_MISMATCH];
        }

        //reset table status
        table = Table();
        postProcess = false;
    }


    if (postProcess){
        //increment command count
        _command_count++;
        if (debug) cout << "||| Incrementing command count for this session\n";

        //show result
        if (debug) cout << setw(30) << "R E S U L T S : \n";
        print_results(_command, table, outs);

//        if (should_drop()){
//            if (debug) cout << "||| Drop table is being invoked\n";

//            table.drop();
//        }
//        else {
//            if (!_mapped_tables.contains(table.get_table_name() + ".bin"))
////                record_table(table);
//            if (debug) cout << "||| Recording retrieved table/n";
        }

//    }
    return true;
}

void SQL::execute_batch(){
    const bool debug = false;
    try {
        if (debug) cout << "||| isBatch! \n";

        string batch_file = build_batch_file_name();
        if (debug) cout << "||| Built batch file name\n";

        run_batch(batch_file.c_str());
    }

    //Errors
    catch (SQL_exceptions e) {
        if (e == INVALID_BATCH_FILE){
            cout << _mapped_exceptions[INVALID_BATCH_FILE];
        }
        else if (e == STREAM_EOF){
            batch_mode = false;
        }
    }

}
string SQL::build_batch_file_name(){
    string batch_file = "";
    vector<string> batch_file_parts = _parsed_command["Batch"];

    for (int i = 0; i < batch_file_parts.size();i++)
//        batch_file.push_back(batch_file_parts[i]);
        batch_file.append(batch_file_parts[i]);

    if (!verify_batch_file(batch_file))
        throw (INVALID_BATCH_FILE);

    return batch_file;

}

bool SQL::verify_batch_file(string str){
    const bool debug = false;

    size_t found = str.find('.');
    if (found != string::npos){
        if (debug) cout << "||| Found DOT position in batch file.\n";
        return true;
    }
    return false;
}

Table SQL::process(int command, string tableName){
    const bool debug = false;
    if (debug) cout << "||| Processing " << command << endl;

    Table table;

    switch (command){
//        case SQL_CREATE :
//        case SQL_MAKE :
//            if (debug) cout << "||| >> SQL_Create called\n";


//            if (_mapped_tables.contains(tableName + ".bin"))
//                if (debug) cout << "contains table name CREATE/MAKE" << endl;
////                table = _mapped_tables[tableName];
//            else {
////                table = Table(tableName, get_fields());
//            }

//            break;

//        case SQL_INSERT :
//            if (debug) cout << "||| >> SQL_Insert called\n";

//            if (_mapped_tables.contains(tableName + ".bin")){
//                if (debug) cout << "contains table name INSERT" << endl;

////                table = Table(tableName);

////                table.insert_into(get_values());
//            }
//            else {
//                throw(UNABLE_TO_PROCESS);
//            }

//            break;

//        case SQL_SELECT :
//            //reindex a table with given name
////            table = Table(tableName);

//            if (is_select_all()){
//                if (is_select_where()){         //Select All
//                    if (debug) cout << "||| SQL_Select * from where called.\n";

////                    table = table._select_all(get_where());

//                }
//                else {
//                    if (debug) cout << "||| SQL_Select all called\n";

////                    table = table._select_all();
//                }
//            }
//            else {
//                if (is_select_where()){
//                    if (debug) cout << "|||SQL_Select <fields> from where called"
//                                    << endl;

////                    table = table.select(get_fields(), get_where());

//                }
//                else /* !is_select_where() */ {//Case 4 Select Fields from
//                    if (debug) cout << "SQL_Select <fields> from called\n";

////                    table = table.select(get_fields());
//                }
//            }
        }

    return table;
}

bool SQL::get_input(char input[], istream& in) throw(SQL_exceptions){
    //ensure input string is parseable

    const bool debug = false;

    if (in.eof()) throw (STREAM_EOF);

    string input_str = "";
    getline(in, input_str);
    strcpy(input, input_str.c_str());

    //If command type Terminate: end
    //else: echo back to user
    int command_type = validate_input(input_str);
    if (debug) cout << "Command Type of " << input_str << " to be "
                    << command_type << endl;

    if (batch_mode){
        if (command_type == NONCOMMAND)
            return false;
    }
    else {
        if (command_type == NONCOMMAND)
            return false;
        else if (command_type == TERMINATE)
            exit(1);
    }
    return true;
}
int SQL::validate_input(string s){
    const bool debug = true;
    if (debug) cout << "Validating " << s[0] << endl;

    int command_no = _mapped_possibilities[s[0]];     //Check if possible

    return command_no;
}

bool SQL::parse(char input[], MMStringString &command_tree){
    const bool debug = false;
    const string src(input);

    try {
        if (debug) cout << "||| Parsing command : " << input << endl;
        Parser parse(input);
        command_tree = parse.get_ParseTree();

    }
    //Errors
    catch (SQL_exceptions e) {

        if (debug) cout << "parse() caught |" << src <<"|"<< endl;

//        cout << get_errorMsg(src.c_str(), e) << endl;

        return false;
    }
    return true;
}

void SQL::drop_table(string table_name){
    _mapped_tables.erase(table_name);
}

//====================== MAP COMMONLY USED VALUES =======================
void SQL::map_commands(){
    const bool debug = false;

    const vector<string> commands = {"create","make","insert","select"};

    if(debug) cout<<"before mapping command: "<<endl;
    for (int i = 0; i < commands.size(); i++)
        _mapped_commands[commands[i]] = i;

    if (debug) cout << "||| Mapped Commands : " <<
                       endl << _mapped_commands << endl;
}
void SQL::map_possibilities(){
    const bool debug = false;

    //if these commands are inserted first, FAIL
    _mapped_possibilities['/'] = NONCOMMAND;
    _mapped_possibilities[' '] = NONCOMMAND;
    _mapped_possibilities['x'] = TERMINATE;

    if (debug) cout << "||| Possible Commands : " <<
                       endl << _mapped_possibilities << endl;
}

void SQL::map_tables(){
    const bool debug = false;

    ifstream in(FILE_TABLERECORD);

    while (!in.eof()){
        string fileName = "";
        getline(in, fileName);

        if (in.eof()) break;

        if (debug) cout << "Retrieving table " << fileName << endl;

        string table_name = fileName + ".bin";

        //create the table based on file
        if (file_exists(fileName.c_str())){
            Table t(table_name);    //not working YET

//            _mapped_tables[fileName] = t;

            if (debug) cout << "Resessioned " << fileName << endl;
        }
    }

    in.close();
}

string SQL::get_errorMsg(const char command[], SQL_exceptions e){
    const bool debug = false;

    if (debug) cout << command << " " << e << endl;

    if (e == ECHO_INPUT)
        return command;
    if (e == STREAM_EOF)
        return _mapped_exceptions[e];
    else if (command[0] != '\0'){
        return _mapped_exceptions[e] + " : " + command;
    }
}

//=================== Parse Tree=======================
int SQL::get_command(){
    const bool debug = false;

    int const COMMAND = 0;

    //get whatever command from the parse tree
    string command = _parsed_command["Command"][COMMAND];
    if (debug) cout << "get_command() << " << command << endl;

    return _mapped_commands[command];
}
vectorstr SQL::get_fields(){
    const bool debug = false;

    if (debug) cout << "||| Returning Fields : \n" << _parsed_command["Fields"];
    return _parsed_command["Fields"];
}

vectorstr SQL::get_values(){
    return _parsed_command["Values"];
}

vectorstr SQL::get_where(){
    const bool debug = false;

    return _parsed_command["Expression"];
}
bool SQL::is_batch(){
    if(_parsed_command.contains("Batch")){
        return true;
    }
    return false;
}

string SQL::get_table(){
    int const NAME = 0;

    return _parsed_command["Table Name"][NAME];
}

bool SQL::is_select_all(){
    if(get_fields()[0] == "*"){
        return true;
    }
    return false;
}

bool SQL::is_select_where(){
    const bool debug = false;

    if (debug) cout << "Current Parse Tree : " << endl << _parsed_command << endl;

    //know there is an expression in Parse Tree
    if(!_parsed_command["Expression"].empty()){
        return true;
    }
    return false;
}
int SQL::get_command_count(){
    return _command_count;
}


//=================== PRINTING ==========================
void SQL::print_description(){
    cout << "_________________________________________________________________\n"
         << setw(47) << " CS8 Final Project: Database System \n"
         << "_________________________________________________________________\n"
         << " Database Program that will They include : \n"
         << " CREATE|MAKE TABLE <TABLENAME> FIELDS <FIELDNAME(S) . . .>\n"
         << " INSERT INTO <TABLE NAME> VALUES <VALUE(S) . . . >\n"
         << " SELECT *|<FIELD(S) . . .> FROM <TABLENAME> WHERE <CONDITION>"
         << endl << endl
         << " <CONDITION> include : <FIELDNAME> <RELATIONAL OPERATOR> <VALUE>"
         << endl
         << " chain conditions together with a <LOGICAL OPERATOR>\n"
         << " <RELATIONAL OPERATOR> : = < > <= >=\n"
         << " <LOGICAL OPERATOR> : AND / OR" << endl
         << "_________________________________________________________________\n";
}
void SQL::print_results(string command, Table table, ostream &outs){
    outs << "[" << _command_count << "] : " << command << endl
         << table << endl;
}
