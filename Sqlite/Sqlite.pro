#-------------------------------------------------
#
# Project created by QtCreator 2015-04-20T16:14:36
#
#-------------------------------------------------

QT      -=gui

TARGET = Sqlite
TEMPLATE = lib

DLLDESTDIR = ../libs

DEFINES += SQLITE_LIBRARY

SOURCES += sqlite.cpp

HEADERS += sqlite.h

INCLUDEPATH += ../MainForm

unix {
    target.path = /usr/lib
    INSTALLS += target
}
