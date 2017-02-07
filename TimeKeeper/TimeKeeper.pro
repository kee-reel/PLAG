#-------------------------------------------------
#
# Project created by QtCreator 2017-01-21T17:03:09
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TimeKeeper
TEMPLATE = app
CONFIG += plugin release

SOURCES += main.cpp\
    pluginmanager.cpp \
    parentwindow.cpp

HEADERS  += \
    pluginmanager.h \
    mainplugininterface.h \
    parentwindow.h \
    interfaces.h
