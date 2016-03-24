QT -= gui
QT += core xml

TARGET = core
CONFIG += staticlib

# qmake does not seem to understand the c++14 option
QMAKE_CXXFLAGS += -std=c++1y

TEMPLATE = lib

SOURCES += \
    introspectionparser.cpp \
    alljoynnode.cpp \
    presentnodesmodel.cpp \
    methodsproxymodel.cpp

HEADERS += \
    introspectionparser.h \
    alljoynnode.h \
    joinedbussession_fw.h \
    presentnodesmodel.h \
    methodsproxymodel.h

include(../AllJoyn-Introspector-Cpp.pri)
