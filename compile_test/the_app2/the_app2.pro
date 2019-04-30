
TEMPLATE = app

SOURCES += $$PWD/main.cpp

CONFIG += c++17

load(configure)
config_testConstexprValue{
    DEFINES *= HAS_CONSTEXPR
}













