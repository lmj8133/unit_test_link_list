include(build/_deps/googletest-src/gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

INCLUDEPATH += $$PWD

SOURCES += \
        main.cpp \
        tst_code_test.cpp \
        src/link_list.c
