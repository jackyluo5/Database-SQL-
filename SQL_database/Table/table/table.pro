TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ../../!includes/Operator/operator.cpp \
        ../../!includes/Operator_relational/relational_operator.cpp \
        ../../!includes/Parser/parser.cpp \
        ../../!includes/RPN/rpn.cpp \
        ../../!includes/Records/record.cpp \
        ../../!includes/STokenizer/stokenizer.cpp \
        ../../!includes/Table/table.cpp \
        ../../!includes/Token/token.cpp \
        ../../!includes/shunting_yard/shunting_yard.cpp \
        main.cpp

HEADERS += \
    ../../!includes/MMap/mmap.h \
    ../../!includes/MPair/mpair.h \
    ../../!includes/Map/map.h \
    ../../!includes/Map_BPT/map_bpt.h \
    ../../!includes/Operator/operator.h \
    ../../!includes/Operator_relational/relational_operator.h \
    ../../!includes/Pair/pair.h \
    ../../!includes/Parser/parser.h \
    ../../!includes/RPN/rpn.h \
    ../../!includes/Records/record.h \
    ../../!includes/SQL_constants/sql_exceptions.h \
    ../../!includes/STokenizer/stokenizer.h \
    ../../!includes/Table/table.h \
    ../../!includes/Token/token.h \
    ../../!includes/shunting_yard/shunting_yard.h \
    ../../!includes/table_constants/table_constants.h \
    ../../../CS3A/!inludes/Intersection/intersection.h \
    ../../../CS3A/!inludes/Queue/queue_iterator_Copy.h \
    ../../../CS3A/!inludes/Stack/stack_iterator_Copy.h \
    ../../../CS3A/!inludes/Vector/vector.h \
    output.h \
    work_report.h
