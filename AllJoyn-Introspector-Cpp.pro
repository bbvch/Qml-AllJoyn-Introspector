QT += core xml
QT -= gui

TARGET = AllJoyn-Introspector
CONFIG += c++14 console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    alljoynhelpers.cpp \
    introspectionlistener.cpp \
    introspectionthread.cpp

DEFINES += QCC_OS_GROUP_POSIX


unix:!macx: LIBS += -L$$PWD/../alljoyn-15.09.00a-src/build/linux/x86_64/debug/dist/cpp/lib/ -lalljoyn -lajrouter

INCLUDEPATH += $$PWD/../alljoyn-15.09.00a-src/build/linux/x86_64/debug/dist/cpp/inc
DEPENDPATH += $$PWD/../alljoyn-15.09.00a-src/build/linux/x86_64/debug/dist/cpp/inc

HEADERS += \
    alljoynhelpers.h \
    introspectionlistener.h \
    introspectionthread.h
