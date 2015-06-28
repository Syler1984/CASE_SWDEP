#-------------------------------------------------
#
# Project created by QtCreator 2015-04-20T16:15:39
#
#-------------------------------------------------

QT       -=gui

TARGET = Postgresql
TEMPLATE = lib

DLLDESTDIR = ../libs

DEFINES += POSTGRESQL_LIBRARY

SOURCES += postgresql.cpp

HEADERS += postgresql.h

INCLUDEPATH += ../MainForm

unix {
    target.path = /usr/lib
    INSTALLS += target
}
