TEMPLATE = app

DESTDIR = $$PWD/../bin
INCLUDEPATH += $$PWD/../include

CONFIG(debug,debug|release){
    TARGET = the_app_debug
}else{
    TARGET = the_app_link
}

win32-msvc*{
    QMAKE_CXXFLAGS += /std:c++latest
}else{
    CONFIG += c++17
    LIBS += -lstdc++fs
}

SOURCES += $$PWD/main.cpp

CONFIG(debug,debug|release){

}else{

}






