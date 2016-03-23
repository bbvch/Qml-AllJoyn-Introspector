QT -= gui
QT += core xml

TARGET = ajintrospect
CONFIG += c++14 staticlib

android {
    QMAKE_CXXFLAGS += -std=c++1y
}

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

unix:!android {
    DEFINES += QCC_OS_GROUP_POSIX
}
android {
    DEFINES += QCC_OS_GROUP_POSIX QCC_OS_ANDROID
}

INCLUDEPATH += $$(AJ_DIST)/cpp/inc
DEPENDPATH += $$(AJ_DIST)/cpp/inc

include(../AllJoyn-Introspector-Cpp.pri)
