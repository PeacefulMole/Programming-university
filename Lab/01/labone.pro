TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    Main/Main/Main.cpp \

DISTFILES += \
    Main/Main/Погода сейчас.html \
    Main/Main/Погода сейчас_files/03n.png \
    Main/Main/Погода сейчас_files/openweathermap-widget-right.min.css \
    Python/python.py

HEADERS += \
    Main/include/cpp_httplib/httplib.h \
    Main/include/nlohmann/adl_serializer.hpp \
    Main/include/nlohmann/byte_container_with_subtype.hpp \
    Main/include/nlohmann/detail/conversions/from_json.hpp \
    Main/include/nlohmann/detail/conversions/to_chars.hpp \
    Main/include/nlohmann/detail/conversions/to_json.hpp \
    Main/include/nlohmann/detail/exceptions.hpp \
    Main/include/nlohmann/detail/hash.hpp \
    Main/include/nlohmann/detail/input/binary_reader.hpp \
    Main/include/nlohmann/detail/input/input_adapters.hpp \
    Main/include/nlohmann/detail/input/json_sax.hpp \
    Main/include/nlohmann/detail/input/lexer.hpp \
    Main/include/nlohmann/detail/input/parser.hpp \
    Main/include/nlohmann/detail/input/position_t.hpp \
    Main/include/nlohmann/detail/iterators/internal_iterator.hpp \
    Main/include/nlohmann/detail/iterators/iter_impl.hpp \
    Main/include/nlohmann/detail/iterators/iteration_proxy.hpp \
    Main/include/nlohmann/detail/iterators/iterator_traits.hpp \
    Main/include/nlohmann/detail/iterators/json_reverse_iterator.hpp \
    Main/include/nlohmann/detail/iterators/primitive_iterator.hpp \
    Main/include/nlohmann/detail/json_pointer.hpp \
    Main/include/nlohmann/detail/json_ref.hpp \
    Main/include/nlohmann/detail/macro_scope.hpp \
    Main/include/nlohmann/detail/macro_unscope.hpp \
    Main/include/nlohmann/detail/meta/cpp_future.hpp \
    Main/include/nlohmann/detail/meta/detected.hpp \
    Main/include/nlohmann/detail/meta/is_sax.hpp \
    Main/include/nlohmann/detail/meta/type_traits.hpp \
    Main/include/nlohmann/detail/meta/void_t.hpp \
    Main/include/nlohmann/detail/output/binary_writer.hpp \
    Main/include/nlohmann/detail/output/output_adapters.hpp \
    Main/include/nlohmann/detail/output/serializer.hpp \
    Main/include/nlohmann/detail/value_t.hpp \
    Main/include/nlohmann/json.hpp \
    Main/include/nlohmann/json_fwd.hpp \
    Main/include/nlohmann/ordered_map.hpp \
    Main/include/nlohmann/thirdparty/hedley/hedley.hpp \
    Main/include/nlohmann/thirdparty/hedley/hedley_undef.hpp

QMAKE_CXXFLAGS += -std=c++17 -pthread
LIBS += -pthread
