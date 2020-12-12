TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS += \
    include/cpp_httplib/httplib.h \
    include/nlohmann/json.hpp


QMAKE_CXXFLAGS += -std=c++20 -pthread
LIBS += -pthread
