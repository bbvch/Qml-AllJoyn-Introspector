TEMPLATE = app

QT += qml quick

TARGET = AllJoyn-Introspector
CONFIG += c++14
CONFIG -= app_bundle

include(../AllJoyn-Introspector-Cpp.pri)
include(../core/core.pri)
include(../ajintrospect/ajintrospect.pri)

SOURCES += main.cpp

RESOURCES += \
    qml.qrc
