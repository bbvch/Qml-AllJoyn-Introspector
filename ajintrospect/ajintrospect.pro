QT -= gui
QT += core xml

TARGET = ajintrospect
CONFIG += c++14 staticlib

TEMPLATE = lib

SOURCES += \
    alljoynhelpers.cpp \
    introspectionlistener.cpp \
    introspectionthread.cpp \
    joinedbussession.cpp \
    ajargumentlist.cpp

HEADERS += \
    alljoynhelpers.h \
    introspectionlistener.h \
    introspectionthread.h \
    joinedbussession.h \
    iobservablebussession.h \
    ajargumentlist.h \
    argumentlist.h

DEFINES += QCC_OS_GROUP_POSIX

INCLUDEPATH += $$PWD/../../alljoyn-15.09.00a-src/build/linux/x86_64/debug/dist/cpp/inc
DEPENDPATH += $$PWD/../../alljoyn-15.09.00a-src/build/linux/x86_64/debug/dist/cpp/inc

include(../AllJoyn-Introspector-Cpp.pri)
