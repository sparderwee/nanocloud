#-------------------------------------------------
#
# Project created by QtCreator 2014-04-06T21:02:04
#
#-------------------------------------------------

QT       += core gui
QT += xml network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opennanoyun
TEMPLATE = app


SOURCES += main.cpp\
        opennanoyun.cpp \
    nonoyun.cpp \
    nanonetwork.cpp

HEADERS  += opennanoyun.h \
    api.h \
    nonoyun.h \
    nanonetwork.h

FORMS    += opennanoyun.ui
CONFIG+=debug
LIBS += -L "C:\sinf\curl\lib" -lcurl
INCLUDEPATH +=C:\sinf\curl\include
LIBS+=C:\sinf\curl\lib\libcurldll.a
RC_FILE = ico.rc
