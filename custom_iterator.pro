TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

HEADERS += \
    container.hpp \
    file.hpp

DISTFILES += \
    1.txt \
    2.txt
