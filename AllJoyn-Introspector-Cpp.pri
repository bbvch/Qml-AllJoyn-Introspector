linux-* {
    CONFIG(debug, debug|release) {
            QMAKE_CXXFLAGS += -fsanitize=address,undefined -g3 -O0
            QMAKE_LFLAGS += -fsanitize=address,undefined -g3 -O0
    }
}
