#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = DataBaseSource
TEMPLATE = lib
QT += core sql

SOURCES += \
    cipherdatabasesourceplugin.cpp

HEADERS += \
    cipherdatabasesourceplugin.h \
    idatabasesource.h

include(../../BuildInfo.pri)

DISTFILES += \
    PluginMeta.json
