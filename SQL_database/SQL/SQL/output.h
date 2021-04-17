#ifndef OUTPUT_H
#define OUTPUT_H

/*
 *
=======================SHUNT YARD=======================
    Vector<Operator> temp;
    vector<string> ins = {
        {"last", "=", "jones", "OR", "first", "=", "bill", "AND", "major", "=", "cs"}
    };

    shunting_yard shunt(ins);

    temp = shunt.infixtopostfix(ins);


INFIX SIZE: 11
last jones   = first bill   = major  cs   = AND  OR




=======================TABLE select all====================
    vectorstr record = {
        {"first", "last", "age", "major"}
    };
    Table table("emp", record);

    //    vectorstr inputs = {
    //        {"joe", "baker", "23", "CS"}
    //    };

    table.insert_into({"joe", "baker", "23", "CS"});
    table.insert_into({"dan", "kidd", "19", "hum"});
    table.insert_into({"mark", "hamill", "44", "actor"});
    table.insert_into({"rick", "daniels", "14", "athlete"});


Table Name : emp
------------------------------------------------------------
    first     last      age    major
------------------------------------------------------------
[0]    first last age major
[1]    joe baker 23 CS
[2]    dan kidd 19 hum
[3]    mark hamill 44 actor
[4]    rick daniels 14 athlete
------------------------------------------------------------





======================TABLE drop========================

Table Name : emp
------------------------------------------------------------
    first     last      age    major
------------------------------------------------------------
[0]    first last age major
[1]    joe baker 23 CS
[2]    dan kidd 19 hum
[3]    mark hamill 44 actor
[4]    rick daniels 14 athlete
------------------------------------------------------------

Table Name : emp
------------------------------------------------------------
    first     last      age    major
------------------------------------------------------------
------------------------------------------------------------




=======================PARSER test==========================
input: select  *  from   emp
keyword:
   [select|3]
   [from|9]
[from|0]
   [emp|17]
   [ * |17]
[ * |17]
   [ |16]


parse tree
   [Table Name|emp ]
   [Fields| *  ]
[Fields| *  ]
   [Command|select ]


   [Table Name|emp ]
   [Fields| *  ]
[Fields| *  ]
   [Command|select ]





==================================SQL================================
Name : Jacky Luo
_________________________________________________________________
           CS8 Final Project: Database System
_________________________________________________________________
 Database Program that will They include :
 CREATE|MAKE TABLE <TABLENAME> FIELDS <FIELDNAME(S) . . .>
 INSERT INTO <TABLE NAME> VALUES <VALUE(S) . . . >
 SELECT *|<FIELD(S) . . .> FROM <TABLENAME> WHERE <CONDITION>

 <CONDITION> include : <FIELDNAME> <RELATIONAL OPERATOR> <VALUE>
 chain conditions together with a <LOGICAL OPERATOR>
 <RELATIONAL OPERATOR> : = < > <= >=
 <LOGICAL OPERATOR> : AND / OR
_________________________________________________________________
Command : create table employee fields first, last, dep, salary
Validating c
input: create   table   employee   fields   first ,  last ,  dep ,  salary
keyword:
       [table|4]
       [salary|17]
   [salary|0]
       [last|17]
   [last|0]
       [first|17]
[first|0]
       [fields|5]
   [fields|0]
       [employee|17]
[employee|0]
       [dep|17]
       [create|0]
   [create|0]
       [, |17]
       [ |16]


parse tree
   [Table Name|employee ]
   [Fields|first ,  last ,  dep ,  salary ]
[Fields|]
   [Command|create ]


Command : insert into employee values johnny, kim, geography, 20000
Validating i
input: insert   into   employee   values   johnny ,  kim ,  geography ,  20000
keyword:
       [values|7]
       [kim|17]
   [kim|0]
       [johnny|17]
   [johnny|0]
       [into|6]
[into|6]
       [insert|2]
   [insert|2]
       [geography|17]
       [employee|17]
[employee|17]
       [20000|17]
       [, |17]
   [, |0]
       [ |16]


parse tree
   [Values|johnny ,  kim ,  geography ,  20000 ]
   [Table Name|employee ]
[Table Name|employee ]
   [Command|insert ]


Command : insert into employee values dan, scheider, director, 60000
Validating i
input: insert   into   employee   values   dan ,  scheider ,  director ,  60000
keyword:
       [values|7]
       [scheider|17]
   [scheider|0]
       [into|6]
   [into|6]
       [insert|2]
[insert|2]
       [employee|17]
       [director|17]
   [director|0]
       [dan|17]
[dan|0]
       [60000|17]
       [, |17]
   [, |17]
       [ |16]


parse tree
   [Values|dan ,  scheider ,  director ,  60000 ]
   [Table Name|employee ]
[Table Name|employee ]
   [Command|insert ]


Command : select * from employee where first = dan
Validating s
input: select  *  from   employee   where   first  =  dan
keyword:
       [where|10]
       [select|3]
   [select|3]
       [from|9]
[from|0]
       [first|17]
       [employee|17]
   [employee|17]
       [dan|17]
       [ = |17]
[ = |17]
       [ * |17]
   [ * |17]
       [ |16]


Command : insert into employee values rick, riordan, author, 102000
Validating i
input: insert   into   employee   values   rick ,  riordan ,  author ,  102000
keyword:
       [values|7]
       [riordan|17]
   [riordan|0]
       [rick|17]
   [rick|0]
       [into|6]
[into|6]
       [insert|2]
   [insert|2]
       [employee|17]
       [author|17]
[author|0]
       [102000|17]
       [, |17]
   [, |0]
       [ |16]


parse tree
   [Values|rick ,  riordan ,  author ,  102000 ]
   [Table Name|employee ]
[Table Name|employee ]
   [Command|insert ]


Command : x
Validating x


*/
#endif // OUTPUT_H
