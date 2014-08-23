QT += core network
QT -= gui

CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app


TARGET = Client


SOURCES += main.cpp \
    ClientExample.cpp

HEADERS += \
    ClientExample.h
