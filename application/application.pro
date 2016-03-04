QT += core
QT -= gui

TARGET = AllJoyn-Introspector
CONFIG += c++14 console
CONFIG -= app_bundle

TEMPLATE = app

include(../AllJoyn-Introspector-Cpp.pri)
include(../core/core.pri)
include(../ajintrospect/ajintrospect.pri)

SOURCES += main.cpp
