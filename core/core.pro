QT -= gui
QT += core xml

TARGET = core
CONFIG += c++14 staticlib

android {
    QMAKE_CXXFLAGS += -std=c++1y
}

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
