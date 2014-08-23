QT += core network
QT -= gui

CONFIG += console
CONFIG -= app_bundle

QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = app


TARGET = Server


SOURCES += main.cpp \
    SslServer.cpp \
    ServerExample.cpp

HEADERS += \
    SslServer.h \
    ServerExample.h
