TEMPLATE = app

QT += qml quick

TARGET = AllJoyn-Introspector
CONFIG -= app_bundle

# qmake does not seem to understand the c++14 option
QMAKE_CXXFLAGS += -std=c++1y

include(../AllJoyn-Introspector-Cpp.pri)
include(../core/core.pri)
include(../ajintrospect/ajintrospect.pri)

SOURCES += main.cpp

RESOURCES += \
    qml.qrc
