TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS += \
    ../../!includes/B+Tree/bplustree.h \
    ../../!includes/BTree/btree.h \
    ../../!includes/MMap/mmap.h \
    ../../!includes/MPair/mpair.h \
    ../../!includes/Map/map.h \
    ../../!includes/Map_BPT/map_bpt.h \
    ../../!includes/Pair/pair.h \
    output.h \
    work_report.h
