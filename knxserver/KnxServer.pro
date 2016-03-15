#-------------------------------------------------
#
# Project created by QtCreator 2012-03-10T16:34:09
#
#-------------------------------------------------

QT       += core gui sql network

TARGET = KnxServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    knxdb.cpp \
    common.cpp \
    QsLogDest.cpp \
    QsLog.cpp \
    QsDebugOutput.cpp

HEADERS  += mainwindow.h \
    knxdb.h \
    common.h \
    QsLogDest.h \
    QsLog.h \
    QsDebugOutput.h

FORMS    += mainwindow.ui \
    groupaddr.ui

RESOURCES += \
    resources.qrc \
    resources.qrc
