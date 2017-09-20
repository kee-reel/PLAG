#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = ExtendableDataManagerPlugin
TEMPLATE = lib
QT += widgets sql

include(../../System/MASS/BuildInfo.pri)

DISTFILES += \
    PluginMeta.json

HEADERS += \
    tablehandler.h \
    extendableitemmodel.h \
    item.h \
    iextendabledatamanager.h \
    extendabledamanager.h

SOURCES += \
    tablehandler.cpp \
    extendableitemmodel.cpp \
    item.cpp \
    extendabledatamanager.cpp
