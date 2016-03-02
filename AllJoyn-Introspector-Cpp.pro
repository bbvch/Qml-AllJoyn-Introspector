QT += core
QT -= gui

TARGET = AllJoyn-Introspector-Cpp
CONFIG += c++14 console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

DEFINES += QCC_OS_GROUP_POSIX


unix:!macx: LIBS += -L$$PWD/../alljoyn-15.09.00a-src/build/linux/x86_64/debug/dist/cpp/lib/ -lalljoyn -lajrouter

INCLUDEPATH += $$PWD/../alljoyn-15.09.00a-src/build/linux/x86_64/debug/dist/cpp/inc
DEPENDPATH += $$PWD/../alljoyn-15.09.00a-src/build/linux/x86_64/debug/dist/cpp/inc

unix:!macx: PRE_TARGETDEPS += $$PWD/../alljoyn-15.09.00a-src/build/linux/x86_64/debug/dist/cpp/lib/liballjoyn.a
