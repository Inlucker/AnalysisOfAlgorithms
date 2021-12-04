TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        conveyor.cpp \
        main.cpp \
        request.cpp \
        timer.cpp \
        tools.cpp

HEADERS += \
    conveyor.h \
    request.h \
    timer.h \
    tools.h
