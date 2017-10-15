#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = DataBaseSource
TEMPLATE = lib
QT += core sql

SOURCES += \
    databasesource.cpp

HEADERS += \
    idatabasesource.h \
    databasesource.h

include(../../BuildInfo.pri)

DISTFILES += \
    PluginMeta.json
