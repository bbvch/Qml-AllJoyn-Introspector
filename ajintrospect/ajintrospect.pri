INCLUDEPATH += $$PWD/

LIBS += -L../ajintrospect/
LIBS += -lajintrospect

PRE_TARGETDEPS += ../ajintrospect/libajintrospect.a

LIBS += -L$$(AJ_DIST)/cpp/lib/ -lajrouter -lalljoyn
