QT += core testlib
QT -= gui

TARGET = test
CONFIG += console
CONFIG -= app_bundle

DEPENDS += gmocklib

# qmake does not seem to understand the c++14 option
QMAKE_CXXFLAGS += -std=c++1y

TEMPLATE = app

SOURCES += \
    introspectionparsertest.cpp \
    presentnodesmodeltest.cpp \
    alljoynnodetest.cpp \
    methodsproxymodeltest.cpp

include(../AllJoyn-Introspector-Cpp.pri)
include(../core/core.pri)

DISTFILES +=

HEADERS += \
    mockbussession.h \
    mockargumentlist.h


INCLUDEPATH += /usr/src/gmock

exists(/usr/src/gmock/gtest/) {
    INCLUDEPATH += /usr/src/gmock/gtest
} else {
    INCLUDEPATH += /usr/src/gtest
}

LIBS += -Lgmock -Lgmock/gtest
LIBS += -lgmock -lgtest -lgmock_main

gmock.target = gmocklib
gmock.commands = mkdir gmock || true; cd gmock; cmake /usr/src/gmock; make

QMAKE_EXTRA_TARGETS += gmock
PRE_TARGETDEPS += gmocklib
