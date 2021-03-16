TEMPLATE = app
CONFIG += c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    tools.cpp \
    caesar.cpp \
    vigenere.cpp

HEADERS += \
    tools.h \
    caesar.h \
    vigenere.h

QMAKE_CXXFLAGS +=   -pedantic-errors\
                    -std=c++17
