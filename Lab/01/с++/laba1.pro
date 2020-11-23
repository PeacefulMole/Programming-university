TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS += \
    Loginer.hpp \
    Option.h \
    cpp_httplib/httplib.h \
    nlohmann/json.hpp

DISTFILES += \
    fole.html
