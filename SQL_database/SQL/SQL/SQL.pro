TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ../../!includes/Operator/operator.cpp \
        ../../!includes/Parser/parser.cpp \
        ../../!includes/Records/record.cpp \
        ../../!includes/SQL/sql.cpp \
        ../../!includes/STokenizer/stokenizer.cpp \
        ../../!includes/Table/table.cpp \
        ../../!includes/Token/token.cpp \
        ../../!includes/shunting_yard/shunting_yard.cpp \
        main.cpp

HEADERS += \
    ../../!includes/MMap/mmap.h \
    ../../!includes/MPair/mpair.h \
    ../../!includes/Map_BPT/map_bpt.h \
    ../../!includes/Operator/operator.h \
    ../../!includes/Pair/pair.h \
    ../../!includes/Parser/parser.h \
    ../../!includes/Records/record.h \
    ../../!includes/SQL/sql.h \
    ../../!includes/STokenizer/stokenizer.h \
    ../../!includes/Table/table.h \
    ../../!includes/Token/token.h \
    ../../!includes/shunting_yard/shunting_yard.h \
    ../../!includes/table_constants/table_constants.h \
    output.h \
    work_report.h
