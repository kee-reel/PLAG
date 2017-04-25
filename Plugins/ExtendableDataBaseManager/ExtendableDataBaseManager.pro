#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = ExtendableDataBaseManagerPlugin
TEMPLATE = lib
QT += core sql

include(../../System/MASS/BuildInfo.pri)

DISTFILES += \
    PluginMeta.json

HEADERS += \
    extendabledatabasemanagerplugin.h \
    iextendabledatabasemanagerplugin.h \
    tablehandler.h \
    extendableitemmodel.h \
    item.h

SOURCES += \
    extendabledatabasemanagerplugin.cpp \
    tablehandler.cpp \
    extendableitemmodel.cpp \
    item.cpp
