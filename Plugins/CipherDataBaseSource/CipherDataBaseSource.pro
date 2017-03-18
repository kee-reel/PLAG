#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = CipherDataBaseSource
TEMPLATE = lib
QT += core sql

SOURCES += \
    cipherdatabasesourceplugin.cpp

include(../../System/MASS/BuildInfo.pri)

HEADERS += \
    cipherdatabasesourceplugin.h \
    ../../Plugins/MainMenuModelPlugin/interfaces.h


DISTFILES += \
    PluginMeta.json
