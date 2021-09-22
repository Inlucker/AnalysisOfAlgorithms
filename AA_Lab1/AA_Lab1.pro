TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Algorithms.cpp \
        main.cpp \
        tools.cpp

HEADERS += \
    Algorithms.h \
    tools.h

#QMAKE_CXXFLAGS += -Ofast
#QMAKE_CXXFLAGS += -O0
