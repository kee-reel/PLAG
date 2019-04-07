#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = DataBase
TEMPLATE = lib
QT += core sql

DEFINES += PLUGIN_BASE_QOBJECT

include(../../Common/BuildInfo.pri)

SOURCES += \
    database.cpp

HEADERS += \
    database.h

DISTFILES += \
    PluginMeta.json
