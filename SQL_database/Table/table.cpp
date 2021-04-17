#include "table.h"


//CTOR
Table::Table(){}

Table::Table(string name){
    load_existing(name);
}

Table::Table(string name, vectorstr field_list){
    const bool debug = true;
    fstream f;

    _name = name;
    _field_list = field_list;
    _file_name = _file_name + ".bin";
    _serial_no = 0;

    open_fileW(f, _file_name.c_str());

    //create a record
    Record r(field_list);

    //write into file name
    r.write(f);

    //set names map
    map_fields();

    //set indices
    indices.resize(field_list.size());

    if(debug)cout<<"this is indices size: "<<indices.size()<<endl;
    if(debug)cout<<"this is name size: "<<_name.size()<<endl;
    if(debug)cout<<"this is _file_name size: "<<_file_name.size()<<endl;
    if(debug)cout<<"this is _field_list size: "<<_field_list.size()<<endl;
    if(debug)cout<<endl<<_map <<endl<<endl;
    if(debug)cout<<endl<<_map2<<endl;

    //close file
    f.close();
}


void Table::load_existing(string name){
    const bool debug = false, print = true;

    //Set table name
    _name = name;
    _file_name = _file_name + "bin";

    //Check if file exists
//    assert(file_exists(_file_name.c_str()));
//    if (!file_exists(_file_name.c_str()))
//        throw (FILE_DNE);

    //Can open and read table name
    ifstream in;
    in.open(_file_name.c_str());

    //Map keywords
    map_fields();

    //Fill vector of fields
    fill_current_fields_from_file(in);
    indices.resize(_field_list.size());
    in.close();


    if (debug) cout << "vectorstr _field_list : " << _field_list << endl;

    if (debug) cout << "map_fields() : " << _map << endl << _map2 << endl;

    //reindex the file
    reindex();

    if (print) print_current_indices("reindex attempt : ");
}


//debug
void Table::print_maps(){
    for (int i = 0; i < _field_list.size(); i++){
        cout << "========= " << _field_list[i] << " =========" << endl
             <<indices[i] << endl;
    }
}

void Table::print_current_indices(string msg){
    cout << msg << endl;
    print_maps();
    cout << endl;
}

//MODIFIERS
void Table::insert_into(vectorstr field_list){
    if (field_list.size() != _field_list.size())
        throw (FIELDS_MISMATCH);

    //open file rw
    //create a record
    //write record into file
    //close file
    fstream f;
    Record r(field_list);

    open_fileRW(f, _file_name.c_str());

    long recno = r.write(f);

    for(long i=0; i<field_list.size(); i++){
        indices[i].insert(field_list[i], recno);
    }

    f.close();
}

void Table::select_all(){
    //open file
    //read rec
    //print record 0
    //print each and every record
    fstream f;
    Record r;

    open_fileRW(f, _file_name.c_str());
    long recno = 0;  //record number

    r.read(f, recno);
    while (!f.eof()){
        cout<<"["<<recno<<"] ";
        cout<<r.get_record()<<endl;
        recno++;

        r.read(f, recno);   //reading next record

    }
    f.close();
}

Table Table::_select_all(){
    //open file
    //read rec
    //print record 0
    //print each and every record
    fstream f;
    Record r;

    open_fileRW(f, _file_name.c_str());
    long recno = 0;  //record number

    r.read(f, recno);
    while (!f.eof()){
        cout<<"["<<recno<<"] ";
        cout<<r.get_record()<<endl;
        recno++;

        r.read(f, recno);   //reading next record

    }
    f.close();
    return Table(_name);
}

Table Table::_select_all(vectorstr conditions){
    //call select where
    return select(_field_list, conditions);
}

Table Table::select(vectorstr field_list){
    fstream f;

    Record full_record;
    vectorstr new_record;
    _serial_no++;

    //open file
    open_fileRW(f, _file_name.c_str());
    long recno = 0;  //record number

    //creating a new name for the table, add serial no.
    _name += std::to_string(_serial_no);

    //make a new table(temporary table)
    Table filtered_table(_name, field_list);

    //Check if created table with right field names
    if (!do_fields_match(filtered_table.get_field_name(), field_list))
        throw (FIELDS_MISMATCH);

//    full_record.read(f, recno);
    while(!f.eof()){
        full_record.read(f, recno);

        cout<<"["<<recno<<"] ";
        cout<<full_record.get_record()<<endl;

        if(f.eof()) break;

        for(int i = 0; i < field_list.size(); i++){
//            indices[i][_field_list[i]] += recno;
            cout<<"get record of this: "<<
                  full_record.get_field_data(_map[field_list[i]]);

            cout<<" map records: "<<_map[field_list[i]]<<endl;
            new_record.push_back(full_record.get_field_data(_map[field_list[i]]));
            _map[field_list[i]] += i;
        }
        cout<<"new record: "<<new_record<<endl;

        filtered_table.insert_into(new_record);
        new_record.clear();

//        cout<<endl<<endl<<filtered_table<<endl<<endl;
        recno++;
        break;
//        full_record.read(f, recno);
    }
    f.close();

//    filtered_table.print_current_indices("selected fields:  ");
    return filtered_table;
}

Table Table::select(vector<string> field_list, vector<string> conditions){
    vector<string> curConditions;

    //get condition of select where
    vector<long> record = get_record_no(conditions);

    const bool debug = false, print = false;



    fstream f;
    Record full_record;
    vector<string> new_record;
    _serial_no++;

    //open file
    open_fileRW(f, _file_name.c_str());
    long recno = 0;  //record number

    //creating a new name for the table, add serial no.
    _name += std::to_string(_serial_no);

    //make a new table(temporary table)
    Table filtered_table(_name, field_list);

    //check if created table with right field names
    if (!do_fields_match(filtered_table.get_field_name(), field_list))
        throw (FIELDS_MISMATCH);

//    full_record.read(f, record[recno]);
    while (!f.eof() && (recno<record.size())){

        if (debug) cout << full_record << endl;

        full_record.read(f, record[recno]);

        if (f.eof()) break;


        for (int j = 0; j < field_list.size(); j++){
            new_record.push_back(full_record.get_field_data(_map[field_list[j]]));
        }
        filtered_table.insert_into(new_record);
        new_record.clear();
        recno++;
    }
    f.close();

    if (print) filtered_table.print_current_indices("selected fields :\n");
    return filtered_table;
}

vector<long> Table::get_record_no(vector<string> statement){
    const bool debug = false;

    Vector<Operator> postfix;
    vector<long> recnos;
    shunting_yard operators;

    //get the postfix from the inputted vector string
    postfix = operators.infixtopostfix(statement);

    //rpn evaluates postfix
    recnos = rpn_evaluate(postfix);
    if(debug) cout<<recnos<<endl;
    return recnos;
}

vector<long> Table::rpn_evaluate(Vector<Operator> postfix){
    const bool debug = true;
    Stack<Operator> ops;
    vector<long> output;
    long result;

    Operator first;
    Operator second;

    cout<<"this is the postfix: "<< postfix<<endl;
    while(!postfix.empty()){
        Operator first_item = postfix.pop_front();

        cout<<"first item: "<<first_item<<endl;
        cout<<"first item prec: "<<first_item.prec()<<endl;

        if(first_item.state() != true){
            if(debug) cout<<"inserted not OP"<<endl;
            //push what is not an OPERATOR into stack
            ops.push_in(first_item);
            cout<<"stack : "<<ops<<endl;
        }
        else{   //case of =, <=, >=, <, >
            if(first_item.prec() == 3){
                if(debug) cout<<"=======================this is OP "<<endl;
                first = ops.pop_back();
                second = ops.pop_back();
                if(debug)cout<<"stack after pop: "<<ops<<endl;
                if("=" == static_cast<Operator>(first_item).op()){
                    //find all first = second
                    //find in multimap
//                    result = indices[]
                }
                if("<=" == static_cast<Operator>(first_item).op()){
                    //find all first <= second
                }
                if(">=" == static_cast<Operator>(first_item).op()){
                    //find all first >= second
                }
                if("<" == static_cast<Operator>(first_item).op()){
                    //find all first < second
                }
                if(">" == static_cast<Operator>(first_item).op()){
                    //find all first > second
                }
                output.push_back(result);
            }//AND
            if(first_item.prec() == 2){
                first = ops.pop_back();
                second = ops.pop_back();
                if("AND" == static_cast<Operator>(first_item).op()){
                    //intersect to find cases for both
                }
            }//OR
            if(first_item.prec() == 1){
                first = ops.pop_back();
                second = ops.pop_back();
                if("OR" == static_cast<Operator>(first_item).op()){
                    //intersect to find cases for both
                }
            }
        }
    }
    //return vector of record numbers
    return output;
}


void Table::drop(){
    const bool debug = false;
    if (debug) cout << "dropping " << _file_name.c_str() << endl;

    if(file_exists(_file_name.c_str())){
        if (debug) cout << _file_name.c_str() << " existed. DROPPING" << endl;

        if (remove(_file_name.c_str()) != 0)
            assert(true && "bin clean up failed\n");
    }
    if(file_exists(_name.c_str())){
        if (debug) cout << _name << " existed. DROPPING" << endl;

        if (remove(_name.c_str()) != 0)
            assert(true && "field clean up failed\n");
    }
}

ostream& Table::print_table(ostream& outs){
    Record record;
    fstream f;
    int i = 0;

    open_fileRW(f, _file_name.c_str());

    outs << "Table Name : " << _name ;
    outs << endl << string(60,'-') << endl;

    //prints out the field list categories
    for (int i = 0; i < _field_list.size(); i++){
        outs << setw(9) << _field_list[i];
    }
    outs << endl << string(60,'-') << endl;

    record.read(f, i);
    while(!f.eof()){

        cout<<"["<<i<<"]    ";
        cout<<record.get_record()<< endl;

        i++;
        record.read(f, i);

    }
    outs << string(60,'-') << endl;
    f.close();
    return outs;
}

bool Table::index(fstream& f, int recno, long &pos){
    Record record;

    pos += record.read(f, recno);

    if (f.eof())
        return false;

    vector<string> field_data = record.vectorize_fields();
    cout<<"this is field data: "<<field_data<<endl;
    for (int i = 0; i < indices.size(); i++)
        indices[i][field_data[i]] += (long) recno;
    return true;
}

void Table::reindex(){
    //index many records

    Record record;
    fstream f;
    long pos = 0;

    open_fileRW(f, _file_name.c_str());
    int recno = 0;

    //Fill vector of MM with indicies from file
    while (index(f,recno, pos)){
        recno++;
    }

    f.close();
}

string Table::get_table_name(){
   return _name;
}

vectorstr Table::get_field_name(){
    return _field_list;
}

void Table::map_fields(){
    const bool debug = false;
    for(int i=0; i<_field_list.size(); i++){
        _map.insert(_field_list[i], i);
    }
    for(int i=0; i<_field_list.size(); i++){
        _map2.insert(i, _field_list[i]);
    }
    if(debug)cout<<endl<<_map<<endl;
    if(debug)cout<<endl<<_map2<<endl;
}

bool Table::do_fields_match(vector<string> src, vector<string> fields){
    if (fields[0] == "*")
        return true;

    for (int i = 0; i < fields.size(); i++)
        if (!contains(src, fields[i]))
            return false;
    return true;

}
//void Table::fill_current_fields(vectorstr fields){
//    const bool debug = false;

//    for (int i = 0; i < fields.size(); i++)
//        _field_list.push_back(fields[i]);

//    if (debug) cout << "fill_current_fields() : " << _field_list << endl;
//}
void Table::fill_current_fields_from_file(ifstream& in){
    const bool debug = true;

    int fields;
    in >> fields;
    in.ignore();

    string field;

    for(int i = 0; i < fields; i++){
        getline(in, field);
        _field_list.push_back(field);
    }

    if (debug) cout << "fill_current_fields_from_file() : " << _field_list
                    << endl;
}
