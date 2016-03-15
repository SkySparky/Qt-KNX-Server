#-------------------------------------------------
#
# Project created by QtCreator 2012-02-19T15:19:11
#
#-------------------------------------------------

QT       += core gui network

TARGET = KnxServerGui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    knxServer.cpp \
    hpai.cpp \
    common.cpp \
    cemi.cpp

HEADERS  += mainwindow.h \
    knxServer.h \
    hpai.h \
    common.h \
    cemi.h

FORMS    += mainwindow.ui
