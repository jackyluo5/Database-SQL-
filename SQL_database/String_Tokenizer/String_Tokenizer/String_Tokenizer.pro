TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ../../!includes/STokenizer/stokenizer.cpp \
        ../../!includes/Token/token.cpp \
        main.cpp

HEADERS += \
    ../../!includes/STokenizer/stokenizer.h \
    ../../!includes/Token/token.h \
    ../../!includes/state_machine_constants/state_machine_constants.h \
    output.h \
    work_report.h
