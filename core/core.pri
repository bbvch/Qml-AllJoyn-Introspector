QT += xml

INCLUDEPATH += $$PWD/

LIBS += -L../core/
LIBS += -lcore

PRE_TARGETDEPS += ../core/libcore.a
