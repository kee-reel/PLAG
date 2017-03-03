#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = TaskDBToolPlugin
TEMPLATE = lib
QT += core sql

windows{
    DESTDIR = ../build-Desktop_Qt_5_8_0_MinGW_32bit-MASS-Release/Modules
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    PluginMeta.json

HEADERS += \
    ../../System/MASS/interfaces.h \
    extendabledatabasemanagerplugin.h \
    iextendabledatabasemanagerplugin.h

SOURCES += \
    extendabledatabasemanagerplugin.cpp
