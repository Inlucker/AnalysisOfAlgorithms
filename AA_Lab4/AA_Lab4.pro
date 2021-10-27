TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        geometric_mean.cpp \
        main.cpp \
        threads.cpp \
        timer.cpp

HEADERS += \
    geometric_mean.h \
    thread_structs.h \
    threads.h \
    timer.h
