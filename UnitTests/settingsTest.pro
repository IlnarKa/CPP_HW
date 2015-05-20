QT       += testlib

QT       -= gui

TARGET = settingsTest
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11
TEMPLATE = app

QMAKE_LFLAGS += -v

SOURCES += settingsTest.cpp \
    settings.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    settings.h

