INCLUDEPATH += $$PWD/

LIBS += -L../ajintrospect/
LIBS += -lajintrospect

PRE_TARGETDEPS += ../ajintrospect/libajintrospect.a

unix:!macx: LIBS += -L$$PWD/../../alljoyn-15.09.00a-src/build/linux/x86_64/debug/dist/cpp/lib/ -lalljoyn -lajrouter
